#include <iostream>
#include <string>
using namespace std;

struct Song {
    string title;
    string artist;
    int ratings[3];
    Song* next;
    Song* prev;
};
void append(Song*& head, Song*& tail, string title, string artist, int r1, int r2, int r3) {
    Song* newSong = new Song;
    newSong->title = title;
    newSong->artist = artist;
    newSong->ratings[0] = r1;
    newSong->ratings[1] = r2;
    newSong->ratings[2] = r3;
    newSong->next = NULL;
    newSong->prev = NULL;

    if (head == NULL) {
        head = tail = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }
}
void nextSong(Song*& current) {
    if (current != NULL && current->next != NULL) {
        current = current->next;
    } else {
        cout << "No next song.\n";
    }
}
void prevSong(Song*& current) {
    if (current != NULL && current->prev != NULL) {
        current = current->prev;
    } else {
        cout << "No previous song.\n";
    }
}
void removeCurrent(Song*& head, Song*& tail, Song*& current) {
    if (current == NULL) return;

    Song* temp = current;

    
    if (current == head) {
        head = current->next;
        if (head != NULL) head->prev = NULL;
    }
    else if (current == tail) {
        tail = current->prev;
        if (tail != NULL) tail->next = NULL;
    }
       else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
  if (temp->next != NULL)
        current = temp->next;
    else
        current = temp->prev;

    delete temp;
}
void display(Song* head, Song* current) {
    Song* temp = head;

    while (temp != NULL) {
        if (temp == current)
            cout << "-> ";
        else
            cout << "   ";

        cout << temp->title << " - " << temp->artist << " | Ratings: ";

        for (int i = 0; i < 3; i++) {
            cout << temp->ratings[i] << " ";
        }

        cout << endl;
        temp = temp->next;
    }
}
int main() {
    Song* head = NULL;
    Song* tail = NULL;
    Song* current = NULL;

    append(head, tail, "Song1", "Artist1", 8, 9, 7);
    append(head, tail, "Song2", "Artist2", 9, 9, 8);
    append(head, tail, "Song3", "Artist3", 7, 8, 8);

    current = head;

    cout << "Initial Playlist:\n";
    display(head, current);

    cout << "\nMove Next:\n";
    nextSong(current);
    display(head, current);

    cout << "\nRemove Current:\n";
    removeCurrent(head, tail, current);
    display(head, current);

    cout << "\nMove Previous:\n";
    prevSong(current);
    display(head, current);

    return 0;
}
