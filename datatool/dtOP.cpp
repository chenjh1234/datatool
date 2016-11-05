#include "dtOP.h"
#include "dtapp.h"
void btCmd::clear()
{
    _stop =0;
    _pause =0;
    _running = 0;
    WIN->runStartAct->setEnabled(true);
    WIN->runPauseAct->setEnabled(false);
    WIN->runStopAct->setEnabled(false);
};
void btCmd::start()
{
    clear();
    _running =1;
    WIN->runStartAct->setEnabled(false);
    WIN->runPauseAct->setEnabled(true);
    WIN->runPauseAct->setToolTip("runPause");
    WIN->runPauseAct->setIcon(ICON_PAUSE);
    WIN->runStopAct->setEnabled(true);
}
void btCmd::stop()
{
    clear();
    _stop = 1;
    WIN->runStartAct->setEnabled(true);
    WIN->runPauseAct->setEnabled(false);
    WIN->runStopAct->setEnabled(false);
}
void btCmd::pause()
{
    clear();
    _pause = 1;
    WIN->runStartAct->setEnabled(false);
    WIN->runPauseAct->setEnabled(true);
    WIN->runPauseAct->setToolTip("runContinue");
    WIN->runPauseAct->setIcon(ICON_CONTINUE);
    WIN->runStopAct->setEnabled(false);
}
void btCmd::goon()
{
    start();
}
