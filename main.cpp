#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>

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

    bool operator<(const Student& other) const {
        // Higher average score comes first
        if (avgScore != other.avgScore) {
            return avgScore > other.avgScore;
        }
        // Compare individual scores from 0 to 8
        for (int i = 0; i < 9; i++) {
            if (scores[i] != other.scores[i]) {
                return scores[i] > other.scores[i];
            }
        }
        // Compare name lexicographically
        return name < other.name;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<string, Student> students;
    set<Student> ranking;
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

            Student s;
            s.name = name;
            s.gender = gender;
            s.classNum = classNum;
            for (int i = 0; i < 9; i++) {
                cin >> s.scores[i];
            }
            s.calculateAvg();
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
                students[it->name].rank = r++;
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
            Student& s = students[name];
            ranking.erase(s);
            s.scores[code] = score;
            s.calculateAvg();
            ranking.insert(s);

        } else if (command == "FLUSH") {
            // Update all ranks
            int r = 1;
            for (auto it = ranking.begin(); it != ranking.end(); ++it) {
                students[it->name].rank = r++;
            }

        } else if (command == "PRINTLIST") {
            int r = 1;
            for (auto it = ranking.begin(); it != ranking.end(); ++it) {
                const Student& s = students[it->name];
                string genderStr = (s.gender == 'M') ? "male" : "female";
                cout << r++ << " " << s.name << " " << genderStr << " "
                     << s.classNum << " " << s.avgScore << "\n";
            }

        } else if (command == "QUERY") {
            string name;
            cin >> name;

            if (!students.count(name)) {
                cout << "[Error]Query failed.\n";
                continue;
            }

            cout << "STUDENT " << name << " NOW AT RANKING "
                 << students[name].rank << "\n";

        } else if (command == "END") {
            break;
        }
    }

    return 0;
}
