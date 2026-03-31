#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

struct Student {
    string name;
    char gender;
    int classNum;
    int scores[9];
    int avgScore;
    int rank;

    void calculateAvg() {
        int sum = 0;
        for (int i = 0; i < 9; i++) {
            sum += scores[i];
        }
        avgScore = sum / 9;
    }
};

struct CompareStudent {
    bool operator()(Student* a, Student* b) const {
        // Higher average score comes first
        if (a->avgScore != b->avgScore) {
            return a->avgScore > b->avgScore;
        }
        // Compare individual scores from 0 to 8
        for (int i = 0; i < 9; i++) {
            if (a->scores[i] != b->scores[i]) {
                return a->scores[i] > b->scores[i];
            }
        }
        // Compare name lexicographically
        return a->name < b->name;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<string, Student*> students;
    set<Student*, CompareStudent> ranking;
    bool started = false;

    string command;
    while (cin >> command) {
        if (command == "ADD") {
            string name;
            char gender;
            int classNum;
            cin >> name >> gender >> classNum;

            if (started) {
                cout << "[Error]Cannot add student now.\n";
                int dummy;
                for (int i = 0; i < 9; i++) cin >> dummy;
                continue;
            }

            if (students.count(name)) {
                cout << "[Error]Add failed.\n";
                int dummy;
                for (int i = 0; i < 9; i++) cin >> dummy;
                continue;
            }

            Student* s = new Student();
            s->name = name;
            s->gender = gender;
            s->classNum = classNum;
            for (int i = 0; i < 9; i++) {
                cin >> s->scores[i];
            }
            s->calculateAvg();
            students[name] = s;

        } else if (command == "START") {
            started = true;
            // Build initial ranking
            for (auto& p : students) {
                ranking.insert(p.second);
            }
            // Update ranks
            int r = 1;
            for (auto it = ranking.begin(); it != ranking.end(); ++it) {
                (*it)->rank = r++;
            }

        } else if (command == "UPDATE") {
            string name;
            int code, score;
            cin >> name >> code >> score;

            if (!students.count(name)) {
                cout << "[Error]Update failed.\n";
                continue;
            }

            // Remove from ranking, update, and re-insert
            Student* s = students[name];
            ranking.erase(s);
            s->scores[code] = score;
            s->calculateAvg();
            ranking.insert(s);
            // DO NOT update ranks here - only on FLUSH

        } else if (command == "FLUSH") {
            // Update all ranks
            int r = 1;
            for (auto it = ranking.begin(); it != ranking.end(); ++it) {
                (*it)->rank = r++;
            }

        } else if (command == "PRINTLIST") {
            int r = 1;
            for (auto it = ranking.begin(); it != ranking.end(); ++it) {
                Student* s = *it;
                string genderStr = (s->gender == 'M') ? "male" : "female";
                cout << r++ << " " << s->name << " " << genderStr << " "
                     << s->classNum << " " << s->avgScore << "\n";
            }

        } else if (command == "QUERY") {
            string name;
            cin >> name;

            if (!students.count(name)) {
                cout << "[Error]Query failed.\n";
                continue;
            }

            cout << "STUDENT " << name << " NOW AT RANKING "
                 << students[name]->rank << "\n";

        } else if (command == "END") {
            break;
        }
    }

    // Cleanup
    for (auto& p : students) {
        delete p.second;
    }

    return 0;
}
