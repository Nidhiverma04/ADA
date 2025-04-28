#include <iostream>
using namespace std;

int main() {
    int n, w;

    cout << "Enter number of frames to be sent: ";
    cin >> n;

    cout << "Enter window size: ";
    cin >> w;

    int* frames = new int[n];
    cout << "Enter the frame data: ";
    for (int i = 0; i < n; ++i) {
        cin >> frames[i];
    }

    cout << "\nSending the frames...\n";

    for (int i = 0; i < n; i++) {
        cout << "Frame " << frames[i] << " sent\n";

        if ((i + 1) % w == 0) {
            cout << "Acknowledgment of above " << w << " frames received!\n\n";
        }
    }

    if (n % w != 0) {
        cout << "Acknowledgment of last " << (n % w) << " frame(s) received!\n";
    }

    delete[] frames;
    return 0;
}



