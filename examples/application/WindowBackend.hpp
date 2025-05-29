#pragma once

class WindowBackend
{
  public:

    struct WindowSize
    {
        int width;
        int height;
    };

    virtual bool initialize_window(int width, int height) = 0;
    
    virtual void process_events() = 0;

    virtual void swap_buffers() = 0;
    
    virtual WindowSize get_window_size() = 0;

    virtual void shutdown() = 0;
};
