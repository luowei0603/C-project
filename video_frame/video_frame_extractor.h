#pragma once
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/time.h>
}
#include <string>

#include "foundry/kernel.h"

namespace foundry::kernel::kaka {
class VideoFrameExtractor {
public:
    VideoFrameExtractor();
    ~VideoFrameExtractor();

    bool openVideo(const std::string &filename);
    void extractFrames(const std::string &outputPath);

private:
    void saveJpg(AVFrame *pFrame, const char *out_name);

    AVFormatContext *formatCtx;
    AVCodecContext *codecCtx;
    AVStream *videoStream;
    int frameRate;
    bool isVideoOpened;
};
}

