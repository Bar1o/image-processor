#pragma once

class Parse {
private:
    const char* open_path_;
    const char* save_path_;

public:
    Parse(){};
    ~Parse(){};

    Parse(int argc, char** argv);
};
