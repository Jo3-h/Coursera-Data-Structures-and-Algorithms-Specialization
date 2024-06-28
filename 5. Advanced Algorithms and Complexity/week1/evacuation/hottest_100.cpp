#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

void get_input(map<string, vector<string> > &out, vector<string> &keys){

    // get input of number of people attending the event
    int people;
    cout<<"How many people are attending?: ";
    cin>>people;
    cin.ignore (numeric_limits<streamsize>::max(), '\n');

    // for each person loop through their song choices
    for (int i=0; i<people; i++){
        string person;
        cout<<"\nEnter name of person  "<<i+1<<": ";
        getline(cin, person);
        for (int j=1; j<3; j++){
            string song_choice;
            cout<<"Enter song "<<j<<": ";
            getline(cin, song_choice);
            if (out.find(song_choice) != out.end()){
                out[song_choice].push_back(person);
            } else {
                out.insert(make_pair(song_choice, vector<string>()));
                out[song_choice].push_back(person);
                keys.push_back(song_choice);
            }
        }
    }

}

void print(map<string, vector<string> > list, vector<string> keys){

    for (int i=0; i<keys.size(); i++){

        cout<<keys[i]<<" - ";
        vector<string> names = list[keys[i]];
        for (int j=0; j<names.size(); j++){
            cout<<names[j]<<" ";
        }
        cout<<"\n";
    }

}

int main(void){

    map<string, vector<string> > songs;
    vector<string> keys;
    get_input(songs, keys);
    print(songs, keys);

    return 0;
}