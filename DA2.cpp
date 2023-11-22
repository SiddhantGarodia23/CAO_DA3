#include <iostream>
#include <bitset>
#include <string>

using namespace std;

int boothsMultiplication(int multiplicand, int multiplier)
{
    bitset<5> M(multiplicand);
    bitset<5> Q(multiplier);
    bitset<5> A(0);
    bitset<1> Q0(0);

    int steps = 5;
    cout << "--------------------------------------------" << endl;
    cout << "Step |\tA \t|\tQ\t|\tQ0" << endl;

    for (int i = 0; i < steps; ++i)
    {
        cout << "--------------------------------------------" << endl;
        if ((Q0[0] == 0 && Q[0] == 1))
        {
            A = A.to_ulong() - M.to_ulong();
        }
        else if ((Q0[0] == 1 && Q[0] == 0))
        {
            A = A.to_ulong() + M.to_ulong();
        }

        int x = A[0];
        int y = A[4];
        int z = Q[0];

        A >>= 1;
        Q >>= 1;
        Q0.set(0, z);
        A.set(4, y);
        Q.set(4, x);
        cout << "  " << i + 1 << "  |  " << A << "\t|\t" << Q << "\t|\t" << Q0 << endl;
    }
    cout << "--------------------------------------------" << endl;

    long f = bitset<10>(A.to_string() + Q.to_string()).to_ulong();

    cout << "\nMultiplication of " << multiplicand << " and " << multiplier << " is " << A << Q << " = " << f << endl;

    return f;
}

int nonRestoringDivision(int Q, int M)
{
    bitset<6> A(0);
    bitset<6> I(M);
    bitset<5> H(Q);
    bitset<1> H0;

    int steps = 5;

    cout << "---------------------------------------" << endl;
    cout << "Step\t|\tA\t|\tH" << endl;

    for (int i = 0; i < steps; ++i)
    {
        int x = H[4];
        A <<= 1;
        H <<= 1;
        A.set(0, x);

        cout << "---------------------------------------" << endl;

        if (A[5] == 0)
        {
            A = A.to_ulong() - I.to_ulong();
        }
        else
        {
            A = A.to_ulong() + I.to_ulong();
        }

        if (A[5] == 0)
        {
            H.set(0, 1);
        }
        else
        {
            H.set(0, 0);
        }

        cout << "  " << 5 - i << "\t|\t" << A << "\t|\t" << H << endl;
    }
    cout << "---------------------------------------" << endl;
    if (A[5] == 1)
    {
        cout << "\nSince MSB of A is 1, we need to add M to A" << endl;
        A = A.to_ulong() + I.to_ulong();
        cout << "A = " << A << endl;
    }
    cout << "Quotient (H): " << H.to_ulong() << endl;
    cout << "Remainder (A): " << A.to_ulong() << endl;

    return H.to_ulong();
}

int binaryAddition(int a, int b)
{

    bitset<5> A(a);
    bitset<5> B(b);
    while (b != 0)
    {
        int carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    bitset<5> C(a);
    cout << " " << A << endl;
    cout << "+" << B << endl;
    cout << "-------" << endl;
    cout << " " << C << endl;
    cout << "\nThe sum is: " << a;

    return a;
}

int binarySubtraction(int a, int b)
{
    int x = b;
    b = ~b + 1;

    bitset<5> A(a);
    bitset<5> B(b);
    while (b != 0)
    {
        int carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    bitset<5> C(a);
    cout << "\n2's compliment of " << x << " is " << B << endl;
    cout << " " << A << endl;
    cout << "+" << B << endl;
    cout << "-------" << endl;
    cout << " " << C << endl;
    cout << "\nThe difference is: " << a;

    return a;
}

int main()
{
    int stamps;
    cout << "Number of stamps Victor has: ";
    cin >> stamps;

    int n1;
    cout << "Number of stamps his friend gave him: ";
    cin >> n1;

    stamps = binaryAddition(stamps, n1);

    cout << "\n\nTherefore the number of stamps victor has is: " << stamps << endl;

    int n2;
    cout << "\nNumber of stamps he gave to his friend: ";
    cin >> n2;

    stamps = binarySubtraction(stamps, n2);

    cout << "\n\nTherefore the number of stamps victor has is: " << stamps << endl;

    int n3, n4;

    cout << "\n\nNo of rows and columns of stamps Victor bought: ";
    cin >> n3 >> n4;
    int f = boothsMultiplication(n3, n4);

    cout << "\nNo of rows and columns of stamps Victor bought is: " << f << endl;

    stamps = binaryAddition(stamps, f);

    cout << "\n\nTherefore the number of stamps victor has is: " << stamps << endl;

    cout << "After sharing stamps equally with his friend: " << endl;

    stamps = nonRestoringDivision(stamps, 2);

    cout << "\nTotal number of stamps Victor has is: " << stamps << endl;

    return 0;
}