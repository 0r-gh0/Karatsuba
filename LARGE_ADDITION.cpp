#include <iostream>
#include <random>
#include <vector>
#include <cctype>

using namespace std;

void display(const vector<char>& numb){
    cout << "\nNUMBER : \n";
    for(int i = 0; i < numb.size(); i++){
        cout << numb[i];
    }cout << endl;
}

vector<char> bigAdd(const vector<char>& numb1, const vector<char>& numb2) {
    int size = numb1.size(), carry = 0, temp;
    vector<char> sum(size);
    for (int i = size - 1; i >= 0; i--) 
    {   
        if (isalpha(numb1[i]))
        {
            if (isalpha(numb2[i])){
                temp = (int(numb1[i]) - 'A' + 10) + (int(numb2[i]) - 'A' + 10) + carry;
            }
            if (isdigit(numb2[i])){
                temp = (int(numb1[i]) - 'A' + 10) + (int(numb2[i]) - '0') + carry;
            }
        }
        if (isdigit(numb1[i]))
        {
            if (isalpha(numb2[i])){
                temp = (int(numb1[i]) - '0') + (int(numb2[i]) - 'A' + 10) + carry;
            }
            if (isdigit(numb2[i])){
                temp = (int(numb1[i]) - '0') + (int(numb2[i]) - '0') + carry;
            }
        }
        if(temp % 16 <= 9){
            sum[i] = char('0' + (temp % 16));
        }
        else{
            sum[i] = char('A' + (temp % 16) - 10);
        }
        carry  = temp / 16;
    }
    if(carry > 0){
        sum.insert(sum.begin(), char('0' + carry));
        sum.shrink_to_fit();
    }
    return sum;
}

vector<char> small_Mult_size4(vector<char>& numb1, vector<char>& numb2){
    vector<char> RESULT(8,'0');
    int temp;
    // NUMB2
    for (int i = 3, count = 0; i >= 0; --i, ++count) {
        int carry = 0;
        vector<char> mult(8,'0');
        //NUMB1
        for (int j = 3; j >= 0; --j) {
            temp = 0;
            if (isalpha(numb1[j]))
            {
                if (isalpha(numb2[i])){
                    temp = (int(numb1[j]) - 'A' + 10) * (int(numb2[i]) - 'A' + 10) + carry;
                }
                if (isdigit(numb2[i])){
                    temp = (int(numb1[j]) - 'A' + 10) * (int(numb2[i]) - '0') + carry;
                }
            }
            if (isdigit(numb1[j]))
            {
                if (isalpha(numb2[i])){
                    temp = (int(numb1[j]) - '0') * (int(numb2[i]) - 'A' + 10) + carry;
                }
                if (isdigit(numb2[i])){
                    temp = (int(numb1[j]) - '0') * (int(numb2[i]) - '0') + carry;
                }
            }
            if(temp % 16 <= 9){
                mult[j + 4 - count] = char('0' + (temp % 16));
            }
            else{
                mult[j + 4 - count] = char('A' + (temp % 16) - 10);
            }
            carry  = temp / 16;
        }

        if (carry > 0) {
            if(carry % 16 <= 9){
                mult[i] = char('0' + (carry % 16));
            }
            else{
                mult[i] = char('A' + (carry % 16) - 10);
            }
        }
        RESULT = bigAdd(mult, RESULT);
        RESULT.shrink_to_fit();
    }
    return RESULT;
}

int main()
{   
    int size, i = 0 , j = 0;

    cout << "Enter length of the Numbers (In Power of 2) : ";
    cin >> size;

    vector<char> numb1(size), numb2(size), sum(size), prod(2*size), SUM(2*size), PROD(2*size);
    vector<char> myArray = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, myArray.size() - 1);

    while( i < size){
        numb1[i] = myArray[distribution(gen)];
        i++;
    }
    while( j < size){
        numb2[j] = myArray[distribution(gen)];
        j++;
    }

    // numb1 = {'F','4','A','D'};
    // numb2 = {'F','A','B','C'};

    // numb1 = {'0','0','A','8','3','6','F','0'};
    // numb2 = {'0','0','0','B','7','8','1','C'};
    
    // numb1 = {'F','0'};
    // numb2 = {'1','C'};

    display(numb1);
    display(numb2);

    cout << "\nTHE SUM IS :: \n";
    display(bigAdd(numb1, numb2));

    cout << "\nPRODUCT IS :: \n";
    display(small_Mult_size4(numb1, numb2));
    cout << "\nDONE !";

    return 0;
}