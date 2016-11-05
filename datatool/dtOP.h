#ifndef DT_OP_H
#define DT_OP_H

#define ICON_CONTINUE QIcon(":/images/runstart.png")
#define ICON_PAUSE QIcon(":/images/runpause.png")

class btCmd
{
public:
    btCmd() {clear();};
    void stop();
    void pause();
    void start();
    void goon();

    bool isPause(){return _pause; };
    bool isStop(){return _stop; };
    void clear();
private:
    
    int _stop,_pause,_running;
};

class dtOP
{
public:
    dtOP(){};
    btCmd btCMD;
};



#endif
