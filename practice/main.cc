#include <iostream>

using namespace std;

int main()
{
    int n;

    cout << "Please enter a number" << endl;
    cin >> n;

    for (int i = 0; i <= 5; i++)
        n += 1;

    cout << "Your number + 5 is: " << n << endl;

    return 0;
}
