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
    startJob();

}
void btCmd::startJob()
{ 
    setEnable(false);
}
void btCmd::endJob()
{ 
    clear();
    setEnable(true);
}
void btCmd::setEnable(bool b)
{ 
    int ib;
    ib = 1;
    if (b) ib = 0; 
    WIN->setEnabledToolbar(WIN->locationToolBar, b);
    if (b)
    {
        if (DOC->bCopyToolbar)
            WIN->setEnabledToolbar(WIN->copyToolBar, b);
    }
    else
        WIN->setEnabledToolbar(WIN->copyToolBar, b);
    WIN->setEnabledToolbar(WIN->dumpToolBar,b);
    WIN->inputV->setBT(ib);
    WIN->outputV->setBT(ib);
    WIN->inputV->setEnabled(b);
    WIN->outputV->setEnabled(b);
}
void btCmd::stop()
{
    clear();
    _stop = 1;
    WIN->runStartAct->setEnabled(true);
    WIN->runPauseAct->setEnabled(false);
    WIN->runStopAct->setEnabled(false);
    endJob();
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
