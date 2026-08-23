#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

// Trạng thái vòng đời của một request
enum RequestState {
    ARRIVED,
    WAITING_UP_PRE,
    READY_P_PROC,
    WAITING_DOWN_PRE,
    READY_P_POST,
    READY_D_PRE,
    WAITING_UP_DEC,
    READY_D_PROC,
    WAITING_DOWN_DEC,
    READY_D_POST,
    FINISHED
};

struct Request {
    int id;
    int lin;
    int cid; // Cloud (remote server) được gán
    RequestState state;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, bytes_per_token, num_layers;
    double S, latency_in_ms, bandwidth_gbps;
    
    // Đọc thông số hệ thống
    cin >> K >> S >> latency_in_ms >> bandwidth_gbps >> bytes_per_token >> num_layers;
    
    double SLO1, SLO2, tp_UB, tp_base, dist_base, w_tp, w_c;
    cin >> SLO1 >> SLO2 >> tp_UB >> tp_base >> dist_base >> w_tp >> w_c;
    
    // Đọc Task-Time Table
    int N;
    if (!(cin >> N)) return 0;
    for (int i = 0; i < N; ++i) {
        double val;
        for (int j = 0; j < 7; ++j) cin >> val;
    }
    
    vector<Request> reqs;
    bool E_free = true;
    vector<bool> C_free(K, true);
    int next_cloud = 0;
    
    string line;
    getline(cin, line); // Bỏ qua ký tự newline
    
    while (true) {
        getline(cin, line);
        if (line == "END" || line.empty()) break;
        
        string t_str = line;
        
        getline(cin, line);
        int e = stoi(line);
        
        // Đọc tất cả các events trong frame
        for (int i = 0; i < e; ++i) {
            getline(cin, line);
            stringstream ss(line);
            string ev_type;
            ss >> ev_type;
            
            if (ev_type == "ARR") {
                int rid, lin;
                ss >> rid >> lin;
                while (reqs.size() <= rid) {
                    reqs.push_back({(int)reqs.size(), 0, -1, FINISHED});
                }
                reqs[rid] = {rid, lin, -1, ARRIVED};
            }
            else if (ev_type == "TDN") {
                string server;
                ss >> server;
                if (server == "E") {
                    E_free = true;
                    string task_type;
                    ss >> task_type; 
                    if (task_type == "P" || task_type == "D") {
                        string sub_task;
                        ss >> sub_task;
                        if (sub_task == "POST") {
                            // Sau D POST, chờ event FIN. Hoặc nếu P POST, chờ thành READY_D_PRE.
                            // Việc cập nhật trạng thái chính sẽ được thực hiện khi nhận event XDN cho input,
                            // Tuy nhiên sau P POST thì sẽ thành READY_D_PRE. Sau D POST sẽ thành READY_D_PRE.
                            // FIN sẽ chốt hạ sau cùng.
                            int val1, val2;
                            if (task_type == "P") {
                                // P POST <remote> <rid> <dur>
                                int remote, rid; double dur;
                                ss >> remote >> rid >> dur;
                                reqs[rid].state = READY_D_PRE;
                            } else {
                                // D POST -1 <m> <rid...> <dur>
                                int minus1, m; double dur;
                                ss >> minus1 >> m;
                                for(int j=0; j<m; ++j) {
                                    int rid; ss >> rid;
                                    // Sẽ sẵn sàng cho vòng lặp tiếp theo, trừ phi bị overwrite bởi FIN
                                    reqs[rid].state = READY_D_PRE; 
                                }
                            }
                        }
                    }
                } else {
                    int cid = stoi(server.substr(1));
                    C_free[cid] = true;
                }
            }
            else if (ev_type == "XDN") {
                string dir, server;
                int size;
                string phase;
                int m;
                ss >> dir >> server >> size >> phase >> m;
                for (int j = 0; j < m; ++j) {
                    int rid;
                    ss >> rid;
                    if (phase == "PRE") {
                        if (dir == "UP") reqs[rid].state = READY_P_PROC;
                        else if (dir == "DOWN") reqs[rid].state = READY_P_POST;
                    } else if (phase == "DEC") {
                        if (dir == "UP") reqs[rid].state = READY_D_PROC;
                        else if (dir == "DOWN") reqs[rid].state = READY_D_POST;
                    }
                }
            }
            else if (ev_type == "FIN") {
                int rid;
                ss >> rid;
                reqs[rid].state = FINISHED;
            }
        }
        
        // Scheduling (Lập lịch)
        vector<string> assignments;
        
        // Quản lý trên Edge (Local Computer)
        if (E_free) {
            bool assigned = false;
            // 1. Ưu tiên D POST
            for (auto& r : reqs) {
                if (r.state == READY_D_POST) {
                    assignments.push_back("E D POST -1 1 " + to_string(r.id));
                    r.state = WAITING_UP_PRE; // Tạm dùng dummy state để đánh dấu đang in-flight
                    E_free = false;
                    assigned = true;
                    break;
                }
            }
            // 2. Kế đến là D PRE
            if (!assigned) {
                for (auto& r : reqs) {
                    if (r.state == READY_D_PRE) {
                        assignments.push_back("E D PRE -1 1 " + to_string(r.id));
                        r.state = WAITING_UP_DEC;
                        E_free = false;
                        assigned = true;
                        break;
                    }
                }
            }
            // 3. Kế đến là P POST
            if (!assigned) {
                for (auto& r : reqs) {
                    if (r.state == READY_P_POST) {
                        assignments.push_back("E P POST " + to_string(r.cid) + " " + to_string(r.id));
                        r.state = READY_D_PRE; // Tạm đánh dấu in-flight
                        E_free = false;
                        assigned = true;
                        break;
                    }
                }
            }
            // 4. Cuối cùng là P PRE
            if (!assigned) {
                for (auto& r : reqs) {
                    if (r.state == ARRIVED) {
                        r.cid = next_cloud;
                        next_cloud = (next_cloud + 1) % K; // Round-robin load balancing
                        assignments.push_back("E P PRE " + to_string(r.cid) + " " + to_string(r.id));
                        r.state = WAITING_UP_PRE;
                        E_free = false;
                        assigned = true;
                        break;
                    }
                }
            }
        }
        
        // Quản lý trên Cloud (Remote Computers)
        for (int c = 0; c < K; ++c) {
            if (C_free[c]) {
                bool assigned = false;
                // Ưu tiên D PROC
                for (auto& r : reqs) {
                    if (r.cid == c && r.state == READY_D_PROC) {
                        assignments.push_back("C" + to_string(c) + " D PROC " + to_string(c) + " 1 " + to_string(r.id));
                        r.state = WAITING_DOWN_DEC;
                        C_free[c] = false;
                        assigned = true;
                        break;
                    }
                }
                // Sau đó tới P PROC
                if (!assigned) {
                    for (auto& r : reqs) {
                        if (r.cid == c && r.state == READY_P_PROC) {
                            assignments.push_back("C" + to_string(c) + " P PROC 0 " + to_string(num_layers) + " " + to_string(c) + " " + to_string(r.id));
                            r.state = WAITING_DOWN_PRE;
                            C_free[c] = false;
                            assigned = true;
                            break;
                        }
                    }
                }
            }
        }
        
        // Flush commands
        cout << assignments.size() << "\n";
        for (const string& cmd : assignments) {
            cout << cmd << "\n";
        }
        cout << flush;
    }
    
    return 0;
}