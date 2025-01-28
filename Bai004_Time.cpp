#include <iostream>
using namespace std;

struct Time{
    int hour;
    int minute;
    int second;
};

Time NextTime (Time current, int x, int y, int z){
    Time next = current;
    next.hour += x;
    next.minute += y;
    next.second += z;

    if (next.second >= 60){
        next.second -=60;
        next.minute++;
    }
    if (next.minute >= 60){
        next.minute -= 60;
        next.hour++;
    }
    while (next.hour > 24) next.hour -= 24;
    if (next.hour == 24) next.hour = 0;
    return next;
}

int main (){
    Time time;
    cout << "Nhap thoi gian: ";
    cin >> time.hour >> time.minute >> time.second;
    if (time.hour >= 24 || time.minute >= 60 || time.second >= 60){
        cout << "Thoi gian khong hop le!" << endl;
    }
    int x, y, z; cin >> x >> y >> z;
    if (y >= 60 || z >= 60){
        cout << "Thoi gian khong hop le!" << endl;
    }
    Time nexttime = NextTime (time, x, y, z);
    cout << "Thoi gian sau do: " << nexttime.hour << ":" << nexttime.minute << ":" << nexttime .second << endl;
}

