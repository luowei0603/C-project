#pragma once
#include "video_frame_extractor.h"
#include <iostream>
#include <iomanip>
#include <fstream>


namespace foundry::kernel::kaka {
VideoFrameExtractor::VideoFrameExtractor()
    : formatCtx(nullptr), codecCtx(nullptr), videoStream(nullptr), frameRate(0), isVideoOpened(false) {
    // av_register_all() is no longer needed in FFmpeg 4.x and above
}

VideoFrameExtractor::~VideoFrameExtractor() {
    if (codecCtx) {
        avcodec_free_context(&codecCtx);
    }
    if (formatCtx) {
        avformat_close_input(&formatCtx);
    }
}

bool VideoFrameExtractor::openVideo(const std::string &filename) {
    if (avformat_open_input(&formatCtx, filename.c_str(), NULL, NULL) != 0) {
        LOG(INFO) << "Could not open input file." << std::endl;
        return false;
    }

    for (int i = 0; i < formatCtx->nb_streams; i++) {
        if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = formatCtx->streams[i];
            const AVCodec *codec = avcodec_find_decoder(videoStream->codecpar->codec_id);
            if (codec) {
                codecCtx = avcodec_alloc_context3(codec);
                avcodec_parameters_to_context(codecCtx, videoStream->codecpar);
                if (avcodec_open2(codecCtx, codec, NULL) == 0) {
                    frameRate = av_guess_frame_rate(formatCtx, videoStream, NULL).num;
                    isVideoOpened = true;
                    return true;
                }
            }
        }
    }

    LOG(INFO) << "Could not find video stream or codec." << std::endl;
    return false;
}

void VideoFrameExtractor::extractFrames(const std::string &outputPath) {
    if (!isVideoOpened) {
        LOG(INFO) << "Video file is not opened correctly." << std::endl;
        return;
    }

     // 获取视频总时长（秒）
    int64_t duration = formatCtx->duration / AV_TIME_BASE;
    LOG(INFO) << "video_duration:" << duration;
    int interval = frameRate; // 每秒提取一帧

    AVPacket packet;
    av_init_packet(&packet);
    AVFrame *frame = av_frame_alloc();
    int64_t frameNumber = 0;

    // 初始化时间戳和帧提取时间点
    int64_t targetPts = 0;
    int64_t frameDuration = AV_TIME_BASE / frameRate;

    while (av_read_frame(formatCtx, &packet) >= 0) {
        if (packet.stream_index == videoStream->index) {
            if (avcodec_send_packet(codecCtx, &packet) == 0) {
                while (avcodec_receive_frame(codecCtx, frame) == 0) {
                    // 计算当前帧的PTS
                    int64_t pts = frame->pts * av_q2d(videoStream->time_base);
                    if (frameNumber * frameDuration >= targetPts) {
                        std::ostringstream filename;
                        filename << outputPath << "/" << frameNumber << ".jpg";
                        LOG(INFO) << "frame filename:" << filename.str();
                        saveJpg(frame, filename.str().c_str());
                        // 更新下一个提取时间点
                        targetPts = (frameNumber + 1) * frameDuration;
                        frameNumber++;
                    }
                    // 如果已经提取完所有需要的帧则退出
                    if (frameNumber >= duration) {
                        av_frame_free(&frame);
                        return;
                    }
                }
            }
        }
        av_packet_unref(&packet);
    }

    av_frame_free(&frame);
}

void VideoFrameExtractor::saveJpg(AVFrame *pFrame, const char *out_name) {
    int width = pFrame->width;
    int height = pFrame->height;

    // 创建输出上下文
    AVFormatContext *pFormatCtx = avformat_alloc_context();
    if (!pFormatCtx) {
        LOG(INFO) << "Could not allocate format context." << std::endl;
        return;
    }

    // 设置输出格式为 MJPEG
    const AVOutputFormat *ofmt = av_guess_format("mjpeg", NULL, NULL);
    pFormatCtx->oformat = ofmt;
    if (!ofmt) {
        LOG(INFO) << "Could not guess format." << std::endl;
        avformat_free_context(pFormatCtx);
        return;
    }

    // 打开输出文件
    if (avio_open(&pFormatCtx->pb, out_name, AVIO_FLAG_WRITE) < 0) {
        LOG(INFO) << "Could not open output file." << std::endl;
        avformat_free_context(pFormatCtx);
        return;
    }

    // 创建新流
    AVStream *pAVStream = avformat_new_stream(pFormatCtx, NULL);
    if (!pAVStream) {
        LOG(INFO) << "Could not create new stream." << std::endl;
        avio_close(pFormatCtx->pb);
        avformat_free_context(pFormatCtx);
        return;
    }

    // 设置编码器参数
    const AVCodec *pCodec = avcodec_find_encoder(AV_CODEC_ID_MJPEG);
    if (!pCodec) {
        LOG(INFO) << "Could not find MJPEG encoder." << std::endl;
        avio_close(pFormatCtx->pb);
        avformat_free_context(pFormatCtx);
        return;
    }

    AVCodecContext *pCodeCtx = avcodec_alloc_context3(pCodec);
    if (!pCodeCtx) {
        LOG(INFO) << "Could not allocate codec context." << std::endl;
        avio_close(pFormatCtx->pb);
        avformat_free_context(pFormatCtx);
        return;
    }

    pCodeCtx->bit_rate = 400000;
    pCodeCtx->width = width;
    pCodeCtx->height = height;
    pCodeCtx->pix_fmt = AV_PIX_FMT_YUVJ420P;
    pCodeCtx->time_base = (AVRational){1, 25}; // 25 fps

    if (avcodec_open2(pCodeCtx, pCodec, NULL) < 0) {
        LOG(INFO) << "Could not open codec." << std::endl;
        avcodec_free_context(&pCodeCtx);
        avio_close(pFormatCtx->pb);
        avformat_free_context(pFormatCtx);
        return;
    }

    if (avcodec_parameters_from_context(pAVStream->codecpar, pCodeCtx) < 0) {
        LOG(INFO) << "Could not copy codec parameters to stream." << std::endl;
        avcodec_free_context(&pCodeCtx);
        avio_close(pFormatCtx->pb);
        avformat_free_context(pFormatCtx);
        return;
    }

    // 写入文件头
    if (avformat_write_header(pFormatCtx, NULL) < 0) {
        LOG(INFO) << "Could not write header." << std::endl;
        avcodec_free_context(&pCodeCtx);
        avio_close(pFormatCtx->pb);
        avformat_free_context(pFormatCtx);
        return;
    }

    // 将帧编码为 JPEG
    AVPacket pkt;
    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;

    if (avcodec_send_frame(pCodeCtx, pFrame) < 0) {
        LOG(INFO) << "Could not send frame for encoding." << std::endl;
        avcodec_free_context(&pCodeCtx);
        avio_close(pFormatCtx->pb);
        avformat_free_context(pFormatCtx);
        return;
    }

    if (avcodec_receive_packet(pCodeCtx, &pkt) < 0) {
        LOG(INFO) << "Could not receive packet from encoder." << std::endl;
        avcodec_free_context(&pCodeCtx);
        avio_close(pFormatCtx->pb);
        avformat_free_context(pFormatCtx);
        return;
    }

    if (av_write_frame(pFormatCtx, &pkt) < 0) {
        LOG(INFO) << "Could not write packet." << std::endl;
        av_packet_unref(&pkt);
        avcodec_free_context(&pCodeCtx);
        avio_close(pFormatCtx->pb);
        avformat_free_context(pFormatCtx);
        return;
    }

    av_packet_unref(&pkt);
    av_write_trailer(pFormatCtx);

    avcodec_free_context(&pCodeCtx);
    avio_close(pFormatCtx->pb);
    avformat_free_context(pFormatCtx);

    return;
}
}

// demo
// VideoFrameExtractor extractor;
// if (extractor.openVideo(inputFilename)) {
//     extractor.extractFrames(outputPath, interval);
// } else {
//     LOG(INFO) << "Failed to open video." << std::endl;
//     return 1;
// }