//20bce219git
//_______________________________________Scheduling_Algorithms___________________________________||
#include "bits/stdc++.h"
using namespace std;
void sjf(vector<pair<int, int>> v)
{
    vector<bool> check(v.size(), false);
    vector<pair<pair<int, int>, int>> x;
    // pair of(pairof(arrival,index),burst);
    int n = v.size();
    for (int i = 0; i < n; i++)
        x.push_back(make_pair(make_pair(v[i].first, i), v[i].second));
    sort(x.begin(), x.end());
    vector<pair<int, int>> gant(n);
    int index = 0;
    gant[index] = (make_pair(x[0].second, x[0].first.second));
    check[x[0].first.second] = true;
    // pair of end time and index;
    for (int i = 0; i < n; i++)
    {
        vector<pair<int, int>> help;
        for (int j = 0; j < n; j++)
        {
            if (i != j && check[x[j].first.second] == false && x[j].first.first <= x[i].second)
            {
                check[x[j].first.second] = true;
                help.push_back(make_pair(x[j].second, x[j].first.second));
            }
        }
        sort(help.begin(), help.end());
        for (int j = 0; j < help.size(); j++)
        {
            index++;
            gant[index] = make_pair(help[j].first + gant[index - 1].first, help[j].second);
        }
    }
    float turnaround;
    float waiting;
    float response;
    float throughput;
    turnaround = 0;
    for (int j = 0; j < n; j++)
    {
        turnaround += gant[j].first - v[gant[j].second].first;
    }
    waiting = 0;
    for (int j = 0; j < n; j++)
    {
        waiting += (gant[j].first - v[gant[j].second].first) - v[gant[j].second].second;
    }
    response = v[gant[0].second].first;
    for (int j = 1; j < n; j++)
    {
        response += gant[j - 1].first - v[gant[j].second].first;
    }
    throughput = gant[n - 1].first;
    throughput /= n;
    cout << "Average Turnaround time is : " << turnaround / v.size() << " ms" << endl;
    cout << "Average waiting time is : " << waiting / v.size() << " ms" << endl;
    cout << "Average response time is :" << response / v.size() << " ms" << endl;
    cout << "Overall throughput  is " << throughput << " ms" << endl;
    cout << "gantt chart : " << endl;
    for (int i = 0; i < n; i++)
    {
        if (i)
        {
            int var = gant[i].first - gant[i - 1].first;
            while (var > 0)
            {
                var--;
                cout << gant[i].second + 1;
                // 1 based index
            }
        }
        else
        {
            int var = gant[i].first - v[gant[i].second].first;
            while (var > 0)
            {
                cout << gant[i].second + 1;
                // 1 based index
                var--;
            }
        }
    }
    cout << endl;
}
void fifo(vector<pair<int, int>> v, vector<int> gant)
{
    float turnaround;
    float waiting;
    float response;
    float throughput;
    for (int i = 0; i < v.size(); i++)
        gant[i] = 0; // initialize with zero
    for (int i = 0; i < v.size(); i++)
    {
        if (i)
        {
            gant[i] += gant[i - 1] + v[i].second;
        }
        else
        {
            gant[i] = v[i].second;
        }
        // gant[i] is process finish time
    }
    turnaround = 0;
    for (int i = 0; i < v.size(); i++)
    {
        turnaround += gant[i] - v[i].first;
        // v[i].first is process arrive time
    }
    waiting = 0;
    for (int i = 0; i < v.size(); i++)
    {
        waiting += (gant[i] - v[i].first) - v[i].second;
        // v[i].second is burst time
    }
    response = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (i)
        {
            response += gant[i - 1] - v[i].first;
            // v[i].first is arrival time
            // gant[i-1] is finish time of previous process means start of current process
            //  which is cpu first time
        }
        else
        {
            response = 0 - v[i].first;
        }
    }
    throughput = gant[gant.size() - 1];
    throughput /= gant.size();
    cout << "Average Turnaround time is : " << turnaround / v.size() << " ms" << endl;
    cout << "Average waiting time is : " << waiting / v.size() << " ms" << endl;
    cout << "Average response time is :" << response / v.size() << " ms" << endl;
    cout << "Overall throughput  is " << throughput << " ms" << endl;
    cout << "gantt chart : " << endl;
    for (int i = 0; i < gant.size(); i++)
    {
        if (i)
        {
            int var = gant[i] - gant[i - 1];
            while (var > 0)
            {
                var--;
                cout << i + 1;
                // 1 based index
            }
        }
        else
        {
            int var = gant[i];
            while (var > 0)
            {
                var--;
                cout << i + 1;
                // 1 based index
            }
        }
    }
    cout << endl;
}
struct srtf_structure
{
    int bt;  // Burst Time
    int art; // Arrival Time
};
void waiting_srtf(srtf_structure proc[], int n, int wt[],int burst[])
{
    cout << "gantt chart : " << endl;
    int done = 0, time = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;
    // until all process completed ...run loop
    while (done != n)
    {
        //find process with min remaining time
        for (int j = 0; j < n; j++)
        {
            if ((proc[j].art <= time) &&
                (burst[j] < minm) && burst[j] > 0)
            {
                minm = burst[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false)
        {
            time++;
            continue;
        }

        // reduce remaining time by one
        burst[shortest]--;
        // update minimum
        minm = burst[shortest];
        if (minm == 0)
            minm = INT_MAX;

        if (burst[shortest] == 0)
        {

            // if burst time is zero then increment complete
            done++;
            check = false;

            // find finish time of current process
            finish_time = time+ 1;

            wt[shortest] = finish_time -proc[shortest].bt -proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        cout << shortest + 1;
        // 1 based index
        time++;
    }
    cout << endl;
    float throughput = finish_time;
    throughput /= n;
    cout << "Overall throughput  is " << throughput << " ms" << endl;
}

void srtf(srtf_structure proc[], int n,int burst[])
{
    int wt[n];
    float turnaround = 0;
    float waiting = 0;
    waiting_srtf(proc, n, wt,burst);
    // Calculate total waiting time and turnaround time
    for (int i = 0; i < n; i++)
    {
        waiting += wt[i];
        // turnaround time=burst time+waiting time
        turnaround += wt[i] + proc[i].bt;
    }

    cout << "Average Turnaround time is : " << turnaround / n << " ms" << endl;
    cout << "Average waiting time is : " << waiting / n << " ms" << endl;
}

struct rr_structure
{
    int arrival;
    int burst;
};

void round_robin(vector<rr_structure> v)
{
    cout << "Enter value of time quanta:" << '\n';
    int quanta;
    cin >> quanta;
    vector<int> rem(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        rem[i] = v[i].burst;
    }
    int temp = 0;
    int wt = 0, at = 0;
    string ans;
    vector<int> comp_time(v.size(), 0);
    int remains = (int)v.size();
    for (int time = 0, i = 0; remains != 0;)
    {
        if (rem[i] <= quanta && rem[i] > 0)
        {
            for (int j = 0; j < rem[i]; j++)
            {
                ans += to_string(i + 1);
            }
            time += rem[i];
            rem[i] = 0;
            temp = 1;
        }
        else if (rem[i] > 0)
        {
            rem[i] -= quanta;
            for (int j = 0; j < quanta; j++)
            {
                ans += to_string(i + 1);
            }
            time += quanta;
        }
        if (rem[i] == 0 && temp == 1)
        {
            remains--;
            comp_time[i] = time;
            wt += time - v[i].arrival - v[i].burst;
            at += time - v[i].arrival;
            temp = 0;
        }
        if (i == v.size() - 1)
        {
            i = 0;
        }
        else if (v[i + 1].arrival <= time)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }
    int mx_c_time = INT_MIN;
    int mn_a_time = INT_MAX;
    for (int i = 0; i < v.size(); i++)
    {
        mx_c_time = max(mx_c_time, comp_time[i]);
        mn_a_time = min(mn_a_time, v[i].arrival);
    }
    cout << "Gantt Chart :";
    cout << ans << '\n';
    cout << "Average Waiting Time:" << wt * 1.0 / v.size() << endl;
    cout << "Average Turnaround Time:" << at * 1.0 / v.size() << endl;
    cout << "Throughput :" << (mx_c_time - mn_a_time) / (float)v.size() << '\n';
}

main()
{
     //20BCE231_RIDDHI_PRAJAPATI
    vector<pair<int, int>> v;
    ifstream indata;
    int arrival_time;
    int burst_time;
    indata.open("input.txt");
    indata >> arrival_time;
    indata >> burst_time;
    int index = 0;
    srtf_structure proc[50];

    while (!indata.eof())
    {
        v.push_back(make_pair(arrival_time, burst_time));
        proc[index] = {burst_time, arrival_time}; // for srtf
        index++;
        indata >> arrival_time;
        indata >> burst_time;
    }
    vector<rr_structure> processes(index);
    int burst[index];
    index = 0;
    for (int i = 0; i < v.size(); i++)
    {
        processes[i].arrival = v[i].first;
        processes[i].burst = v[i].second;
        burst[i]=v[i].second;
    }
    indata.close();
    vector<int> gant(v.size());
    // turn around time=process finish time - process arrival time
    // waiting time =turn around time - burst time
    // response time =cpu first time - arrival time
    //  overall throughput=total time/total number of processes
    while (1)
    {
        cout << "|---------------------------------------------|" << endl;
        cout << "|1.first come first served(FIFO)              |" << endl;
        cout << "|2.shortest job first(SJF)                    |" << endl;
        cout << "|3.shortest remaining time first(SRTF)        |" << endl;
        cout << "|4.round robin(RR)                            |" << endl;
        cout << "|5.Exit                                       |" << endl;
        cout << "|---------------------------------------------|" << endl;
        cout << "|---------------Enter your choice-------------|\n";
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "first come first served(FIFO)" << endl;
            fifo(v, gant);
            break;
        case 2:
            cout << "shortest job first(SJF)" << endl;
            sjf(v);
            break;
        case 3:
            cout << "shortest remaining time first(SRTF)" << endl;
            srtf(proc, v.size(),burst);
            break;
        case 4:
            cout << "round robin(RR)" << endl;
            round_robin(processes);
            break;
        case 5:
            return 0;
        default:
            cout << "Incorrect Choice !! enter correct choice." << endl;
            break;
        }
    }
}