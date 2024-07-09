#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Information {
  string track;
  string name;
  string streams;
  bool explicitTrack;
};

void readData(fstream& in, vector<Information>& data) {
  string line;
  getline(in, line);
  while (getline(in, line)) {
    Information temp;
    int i = 1;
    while (line[i] != '\"') {
      temp.track += line[i];
      i++;
    }
    i += 3;
    while (line[i] != '\"') {
      temp.name += line[i];
      i++;
    }
    i += 2;
    while (line[i] != ',') {
      temp.streams += line[i];
      i++;
    }
    i += 1;
    if (line[i] == '1') {
      temp.explicitTrack = true;
    } else {
      temp.explicitTrack = false;
    }
    data.push_back(temp);
  }
  in.close();
}

void filterSongs(vector<Information>& data) {
  for (int i = 0; i < data.size(); i++) {
    if (data[i].explicitTrack) {
      data.erase(data.begin() + i);
      i--;
    }
  }
}

void sortSongs(vector<Information>& data) {
  for (int i = 0; i < data.size() - 1; i++) {
    for (int j = i + 1; j < data.size(); j++) {
      if (data[i].streams < data[j].streams) {
        swap(data[i], data[j]);
      }
    }
  }
}

void countArtistWithMostSongs(vector<Information>& data) {
  vector<string> artist;
  vector<int> count;
  for (int i = 0; i < data.size(); i++) {
    bool found = false;
    for (int j = 0; j < artist.size(); j++) {
      if (data[i].name == artist[j]) {
        count[j]++;
        found = true;
        break;
      }
    }
    if (!found) {
      artist.push_back(data[i].name);
      count.push_back(1);
    }
  }
  int max = count[0];
  for (int i = 1; i < count.size(); i++) {
    if (count[i] > max) {
      max = count[i];
    }
  }
  cout << "Artist of the year: ";
  for (int i = 0; i < count.size(); i++) {
    if (count[i] == max) {
      cout << artist[i] << " with " << count[i] << " songs." << endl;
      break;
    }
  }
}

int main() {
  fstream in("MostStreamedSpotifySongs2024.txt", ios::in);
  fstream out("filtered_songs.txt", ios::out);
  vector<Information> data;
  readData(in, data);
  filterSongs(data);
  for (int i = 0; i < data.size(); i++) {
    out << data[i].track << ", " << data[i].name << ", " << data[i].streams
        << endl;
  }
  sortSongs(data);
  cout << "Top 5 songs by streams: \n";
  for (int i = 0; i < 5; i++) {
    cout << i + 1 << ". " << data[i].track << ", " << data[i].name << ", "
         << data[i].streams << endl;
  }
  countArtistWithMostSongs(data);

  return 0;
}