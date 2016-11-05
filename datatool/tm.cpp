#include "sys/time.h"
#include "sys/times.h"
#include "unistd.h"
#include <iostream>
using namespace std;
#if 0
#include <sys/time.h>
//CLOCKS_PER_SEC
time_t clock();
struct timeval 
{
      time_t      tv_sec;     /* seconds */
      suseconds_t tv_usec;    /* microseconds */
};
int gettimeofday(struct timeval *tv, struct timezone *tz);

struct tms 
{
      clock_t tms_utime;  /* user time */
      clock_t tms_stime;  /* system time */
      clock_t tms_cutime; /* user time of children */
      clock_t tms_cstime; /* system time of children */

};
clock_t getCputime()
{
	struct tms cpuTime;
	if( times( &cpuTime ) == -1 )
		return -1;
	return cpuTime.tms_utime + cpuTime.tms_stime;	
}
#endif
#define MAX_SUMU 10*1000*1000 // 10S
/**
 * statistic : 
 * time elapsed 
 * cpu time 
 * bytes;
 * files; 
 * 
 * @author cjh (9/22/2016)
 */
class sumInfo
{   
public:
    sumInfo(){sumS = 0; sumU = 0;counter = 0;bytes = 0;cpu = 0;files = 0;};
    /// start the time counter
    int start();
    /// count the time since start(), in microSecond=S/1000000;
    long  elapsed(); 

    /// get the time that all of strt-elapsed of this object;
    double getTime(){ return sumS + double(sumU)/1000000;};
    /// get cpu time that all of strt-elapsed of this object;
    double getCpu(){return  double(cpu)/sysconf(_SC_CLK_TCK);};
    /// couner of start-elapsed;
    long size(){return counter;};
    /// couner of bytes;
    long getBytes();
    void addBytes(int by){bytes += by;};
    /// couner of file;
    long getFiles();
    void addFiles(int by){files += by;};

    /// get cpu clock_t for this process
    long getCputime();
private:
    struct timeval tv0;// start time
    long  sumU;
    double sumS;
    long counter; // tims of stat-elapsed;
    long bytes;
    long cpu0,cpu;
    int files;
};

long sumInfo::getCputime()
{
	struct tms cpuTime;
    long l;
	if( times( &cpuTime ) == -1 )
		return -1;
	l = cpuTime.tms_utime + cpuTime.tms_stime;	
    return l;//sysconf(_SC_CLK_TCK);//= 100; so the accuracy is 1/100S;
};
int sumInfo::start()
{
    struct timeval tv;
    if(gettimeofday( &tv, NULL ) == 0)
    {
        tv0 = tv;
        cpu0 = getCputime();
        return 0;
    }
    return -1;
};
 
long  sumInfo::elapsed() 
{
    struct timeval tv;
    long  u;
    if(gettimeofday( &tv, NULL ) == 0)
    {
        // time:
        u = (tv.tv_sec-tv0.tv_sec)*1000000 + (tv.tv_usec-tv0.tv_usec);
        sumU += u;
        // counter of record;
        counter ++;
        //cout <<sumU <<"," << u<<endl;
        //cpu
        cpu += getCputime() - cpu0;
        cpu0 = 0;
        if (sumU >= MAX_SUMU) 
        {
            //cout << "dddddddddddd" <<MAX_SUMU <<endl;
            sumS += double(sumU)/1000000;
            
            sumU = 0;
        }
        return u;
    }
    return -1; 
};
#if 0
double elapsed()
{
    struct timeval tv
        gettimeofday( &tv1, NULL ); //static run time	
		begin_cputime = gos_get_cputime();	
		m_modexec->ExecPM();
		end_cputime = gos_get_cputime();
		gettimeofday( &tv2, NULL );
		modElapsedTime = (double)(tv2.tv_sec-tv1.tv_sec) +((double)(tv2.tv_usec-tv1.tv_usec))/1000000;
		m_modexec->m_iRunTimesPM += modElapsedTime;
};
#endif
main()
{
    sumInfo tm;
    double d;
    int i;
    cout << "start" <<endl;
    tm.start();
    cout << "do the loop " <<endl;
    for (i = 0; i < 1024 * 32768; ++i) ; 
    cout << "sleep 1 second" <<endl;
    sleep(1);
    cout << "CLOCKS_PER_SEC = " << CLOCKS_PER_SEC <<endl;
    cout << "sysconf(_SC_CLK_TCK)= " << sysconf(_SC_CLK_TCK) <<endl;
    // getTime =0 because it run getTime first ,than run elapsed;
    cout << "tm elapsed= " << tm.elapsed() << ","<< tm.getTime() << endl;
    cout << "tm elapsed= " << tm.elapsed() << endl;
    cout << "tm getTime= " << tm.getTime() <<endl;
    cout << "t.cputime = " << tm.getCputime()<< endl;
    cout << "clock= " << clock() <<endl; // accuracy is the same with times;
    cout << "size of int  long,ll = " << sizeof(int) << ","<< sizeof(long)<< ","<< sizeof(long long) <<endl;
     cout << "t.getCpu = " << tm.getCpu()<< endl;
}
#if 0
start
do the loop
sleep 1 second
CLOCKS_PER_SEC = 1000000
sysconf(_SC_CLK_TCK)= 100
1069648,1069648
tm elapsed= 1069648,0
2139326,1069678
tm elapsed= 1069678
tm getTime= 2.13933
t.cputime = 6
clock= 60000  // 1/100 
size of int  long,ll = 4,8,8
#endif
