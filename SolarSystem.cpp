#include <bits/stdc++.h>
#define pi acos(-1.0)
using namespace std;

const double G=6.61e-11;
const double M=1.989E30;
const double dt=3600;
const double year=86400*365.25;
const double day=86400;
const double Me=5.972E24;

double v (double r,double t){
    return 2*pi*r/t;
}

struct Planet{
    double m;
    double x,y,z;
    double vx,vy,vz;
    double ax,ay,az;
    void init(double _m,double _x,double _y,double _z,double _vx,double _vy,double _vz){
        m=_m,x=_x,y=_y,z=_z,vx=_vx,vy=_vy,vz=_vz;
    }
    double R(){
        return sqrt(x*x+y*y+z*z);
    }
    void evolution(){
        vx+=ax*dt;
        vy+=ay*dt;
        vz+=az*dt;
        x+=vx*dt;
        y+=vy*dt;
        z+=vz*dt;
    }
} P[10];

int main(){
    int n=8;
    P[0].init(0.055*Me,57.909175E9,0,0,0,v(57.909175E9,87.97*day)*cos(0),v(57.909175E9,87.97*day)*sin(0));
    P[1].init(0.815*Me,108.20893E9,0,0,0,v(108.20893E9,224.7*day)*cos(0),v(108.20893E9,224.7*day)*sin(0));
    P[2].init(1*Me,149.59789E9,0,0,0,v(149.59789E9,365.24*day)*cos(pi/6),v(149.59789E9,365.24*day)*sin(pi/6));
    P[3].init(0.10744*Me,227.93664E9,0,0,0,v(227.93664E9,686.93*day)*cos(pi/12),v(227.93664E9,686.93*day)*sin(pi/12));
    P[4].init(317.82*Me,778.41202E9,0,0,0,v(778.41202E9,11.8565*year)*cos(0),v(778.41202E9,11.8565*year)*sin(0));
    P[5].init(95.16*Me,1426.7254E9,0,0,0,v(1426.7254E9,29.448*year)*cos(0),v(1426.7254E9,29.448*year)*sin(0));
    P[6].init(14.371*Me,2870.9722E9,0,0,0,v(2870.9722E9,84.02*year)*cos(0),v(2870.9722E9,84.02*year)*sin(0));
    P[7].init(17.147*Me,4498.2529E9,0,0,0,v(4498.2529E9,164.79*year)*cos(0),v(4498.2529E9,164.79*year)*sin(0));
    FILE* f=fopen("good.txt","w");
    int cnt=0;
    int period=24*10;
    for(double t=0;t<10000*year;t+=dt){
        if(cnt%period==0 && (t<=10*year || t>=9990*year))  fprintf(f,"%f\n",t);
        for(int i=0;i<n;i++){
            double a=-G*M/P[i].R()/P[i].R();
            P[i].ax=a/P[i].R()*P[i].x;
            P[i].ay=a/P[i].R()*P[i].y;
            P[i].az=a/P[i].R()*P[i].z;
            for(int j=0;j<n;j++){
                if(i==j) continue;
                double dx=P[i].x-P[j].x;
                double dy=P[i].y-P[j].y;
                double dz=P[i].z-P[j].z;
                double r=sqrt(dx*dx+dy*dy+dz*dz);
                a=-G*P[j].m/r/r;
                P[i].ax+=a/r*dx;
                P[i].ay+=a/r*dy;
                P[i].az+=a/r*dz;
            }
            P[i].evolution();
            if(cnt%period==0 && (t<=10*year || t>=9990*year))   fprintf(f,"%f %f %f\n",P[i].x,P[i].y,P[i].z);
        }
        cnt++;
    }
}

