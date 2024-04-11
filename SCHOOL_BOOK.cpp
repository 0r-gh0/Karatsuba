#include <iostream>
#include <random>
#include <vector>

using namespace std;

void display(const vector<char>& numb){
    cout << "NUMBER : \n";
    for(char i : numb){
        cout << i;
    }cout << endl;
}

void eqLength(vector<char>& numb1, vector<char>& numb2){
    while (numb1.size() < numb2.size()) {
        numb1.emplace(numb1.begin(), '0');
    }
    while (numb2.size() < numb1.size()) {
        numb2.emplace(numb2.begin(), '0');
    }
}

vector<char> remZero(vector<char>& vec){
    int N = vec.size(), count = 0;
    while(count < N - 1){
        if (vec[0] == '0'){
            vec.erase(vec.begin());
        }
        else{break;}
    }
    return vec;
}

vector<char> bigAdd(vector<char>& numb1, vector<char>& numb2) {
    vector<char> sum;
    eqLength(numb1, numb2);
    int size = numb1.size(), carry = 0, temp;
    for (int i = size - 1; i >= 0; i--) {
        temp = (numb1[i] - '0') + (numb2[i] - '0') + carry;
        sum.emplace(sum.begin(), char('0' + temp % 10));
        carry = temp / 10;
    }
    if (carry > 0) {
        sum.emplace(sum.begin(), char('0' + carry));
    }
    return remZero(sum);
}

vector<char> bigMult(const vector<char>& numb1, const vector<char>& numb2){
    int end = numb2.size() - 1, size = numb1.size() - 1, count = 0, carry , temp;
    vector<char> mult, RESULT;
    while(end >= 0){
        carry = 0;
        for(int i = size; i >= 0; i--){
            temp = (numb1[i] - '0')*(numb2[end] - '0') + carry;
            mult.emplace(mult.begin(), char('0' + temp % 10));
            carry = temp / 10;
        }
        if (carry > 0) {
            mult.emplace(mult.begin(), char('0' + carry));
        }
        for(int j = 0; j < count; j++){
            mult.push_back('0');
        }count++;
        RESULT = bigAdd(mult, RESULT);
        mult.clear();
        end--;
    }
    if (RESULT[0] == '0' && RESULT[1] != '0'){
        RESULT.erase(RESULT.begin());
    }
    return remZero(RESULT);
}

vector<char> bigSub(vector<char>& numb1, vector<char>& numb2) {
    vector<char> sub;
    eqLength(numb1, numb2);
    int size = numb1.size(), carry = 0, temp, temp1, temp2;
    for (int i = size - 1; i >= 0; i--) {
        if( numb1[i] - '0' > numb2[i] - '0'){
                
        }
        else{

        }
        temp = (numb1[i] - '0') + (numb2[i] - '0') + carry;
        sub.emplace(sub.begin(), char('0' + temp % 10));
        carry = temp / 10;
    }
    if (carry > 0) {
        sub.emplace(sub.begin(), char('0' + carry));
    }
    return remZero(sub);
}

int main(){
    int i = 0 , j = 0, power_of_two;
    vector<char> numb1, numb2, sum, prod, SUM, PROD;
    vector<char> myArray = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, myArray.size() - 1);

    while( i < 100){
        numb1.push_back(myArray[distribution(gen)]);
        i++;
    }
    while( j < 100){
        numb2.push_back(myArray[distribution(gen)]);
        j++;
    }
    numb1 = remZero(numb1);
    numb2 = remZero(numb2);

    display(numb1);
    display(numb2);

    cout << "\nSUM IS :: ";
    SUM = bigAdd(numb1, numb2);
    display(SUM);

    cout << "PRODUCT IS :: ";
    PROD = bigMult(numb1, numb2);
    display(PROD);
    cout << "DONE !";

    return 0;
}
