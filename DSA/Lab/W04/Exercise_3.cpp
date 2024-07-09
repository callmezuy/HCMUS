#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Candidate {
  string name;
  float pt1;
  float pt2;
  float avg;
  vector<int> preferences;
};

struct Option {
  int id;
  int maxAdmitted;
  vector<Candidate> admittedCandidates;
};

void getInput(fstream &in, int &m, vector<Option> &options,
              vector<Candidate> &candidates);
bool compareCandidates(Candidate a, Candidate b);
void assignOptions(vector<Option> &options, vector<Candidate> &candidates);
void makeOutput(fstream &out, vector<Option> &options,
                vector<Candidate> &candidates);

int main() {
  fstream in("Exercise_3.txt", ios::in);
  if (!in) {
    cout << "Cannot open the input file" << endl;
    return 1;
  }
  fstream out("Exercise_3_output.txt", ios::out);
  if (!out) {
    cout << "Cannot open the output file" << endl;
    return 1;
  }

  int m;
  vector<Option> options;
  vector<Candidate> candidates;
  getInput(in, m, options, candidates);

  // print input

  //   for (auto &option : options) {
  //     cout << "Option " << option.id << " " << option.maxAdmitted << endl;
  //   }
  //   for (auto &candidate : candidates) {
  //     cout << "Candidate " << candidate.name << " " << candidate.pt1 << " "
  //          << candidate.pt2 << " " << candidate.avg << endl;
  //     for (auto &preference : candidate.preferences) {
  //       cout << preference << " ";
  //     }
  //     cout << endl;
  //   }

  assignOptions(options, candidates);
  makeOutput(out, options, candidates);
  in.close();
  out.close();

  return 0;
}

void getInput(fstream &in, int &m, vector<Option> &options,
              vector<Candidate> &candidates) {
  in >> m;
  for (int i = 0; i < m; i++) {
    Option option;
    in >> option.id >> option.maxAdmitted;
    options.push_back(option);
  }
  string temp;
  in.ignore();
  while (getline(in, temp, ',')) {
    Candidate candidate;
    for (int i = 0; i < temp.size(); i++) {
      if (isalpha(temp[i]) || isspace(temp[i])) candidate.name += temp[i];
    }
    in >> candidate.pt1;
    in.ignore();
    in >> candidate.pt2;
    in.ignore();
    candidate.avg = (candidate.pt1 + candidate.pt2) / 2;
    for (int i = 0; i < m; i++) {
      int opt;
      in >> opt;
      in.ignore();
      candidate.preferences.push_back(opt);
    }
    candidates.push_back(candidate);
  }
}

bool compareCandidates(Candidate a, Candidate b) {
  if (a.avg != b.avg) return a.avg > b.avg;
  if (a.pt1 != b.pt1) return a.pt1 > b.pt1;
  return a.pt2 > b.pt2;
}

void assignOptions(vector<Option> &options, vector<Candidate> &candidates) {
  if (options.empty() || candidates.empty()) return;

  sort(candidates.begin(), candidates.end(), compareCandidates);

  for (auto &candidate : candidates) {
    bool admitted = false;
    for (auto &preference : candidate.preferences) {
      if (preference <= 0 || preference > options.size()) continue;

      Option &option = options[preference - 1];
      if (option.admittedCandidates.size() < option.maxAdmitted) {
        option.admittedCandidates.push_back(candidate);
        admitted = true;
        break;
      } else {
        Candidate &lastAdmittedCandidate = option.admittedCandidates.back();
        if (candidate.avg == lastAdmittedCandidate.avg &&
            candidate.pt1 == lastAdmittedCandidate.pt1 &&
            candidate.pt2 == lastAdmittedCandidate.pt2) {
          option.admittedCandidates.push_back(candidate);
          admitted = true;
          option.maxAdmitted += 1;
          break;
        }
      }
    }
    if (!admitted) {
      return;
    }
  }
}

void makeOutput(fstream &out, vector<Option> &options,
                vector<Candidate> &candidates) {
  for (auto &option : options) {
    out << "Successful candidates for option " << option.id << endl;
    int rank = 1;
    for (auto &candidate : option.admittedCandidates) {
      out << rank << "." << candidate.name << " " << candidate.avg << endl;
      rank++;
    }
  }
  int pos = 0;
  for (auto &option : options) {
    pos += option.maxAdmitted;
  }
  out << "Unsuccessful candidates" << endl;
  int count = 0;
  int rank = 1;
  for (auto &candidate : candidates) {
    if (count >= pos) {
      out << rank << "." << candidate.name << " " << candidate.avg << endl;
      rank++;
    }
    count++;
  }
}
