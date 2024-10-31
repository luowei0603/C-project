#include <thread>
#include <future>
#include <vector>
#include <experimental/algorithm>  
using std::experimental::latch;

class my_data{};
my_data make_data();
void do_more_stuff();
void process_data(my_data*, unsigned cnst);
void foo() {
    unsigned const thread_count = 2;
    latch done(thread_count);
    my_data data[thread_count];
    std::vector<std::future<void>> threads;
    for (unsigned i = 0; i < thread_count; i++) {
        threads.push_back(std::async(std::launch::async, [&,i]{
            data[i] = make_data();
            done.count_down();
            do_more_stuff();
        }));
    }
    done.wait();
    process_data(data, thread_count);
}