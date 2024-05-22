#include  <iostream>
#include  <string>
using namespace std;
void sort(string r[], int x)
{
    string first;
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 29; j++)
        {
            if (r[j] == "e")
            {
                first = r[j + 1];
                r[j + 1] = r[j];
                r[j] = first;
            }
        }
    }
}
int OR(string x, string y)
{
    if (x == "0" && y == "0")
        return '0';
    else
        return '1';
}
int AND(string x, string y)
{
    if (x == "0" || y == "0")
        return '0';
    else
        return '1';
}
int NOT(string x)
{
    if (x == "0")
        return '1';
    else
        return '0';
}
int XOR(string x, string y)
{
    if (x == "1" && y == "1")
        return '0';
    else if (x == "1" || y == "1")
        return '1';
    else
        return '0';
}
int NAND(string x, string y)
{
    if (x == "1" && y == "1")
        return '0';
    else
        return '1';
}
int NOR(string x, string y)
{
    if (x == "0" && y == "0")
        return '1';
    else
        return '0';
}
int search(char x, string arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (x == arr[i])
            return 0;
    }
    return 1;

}
void V_to_C(char Char, char Variable, string arr[]) // variables to missing value
{
    for (int i = 0; i < 30; i++)
    {
        if (arr[i][0] == Variable && arr[i].size() == 1)
            arr[i] = Char;
    }
}

int main()
{
    int A = 0;
    int counter_AND = 0, counter_OR = 0, counter_NOT = 0;
    int counter_NAND = 0, counter_NOR = 0, counter_XOR = 0;
    int counter_of_variables = 0;
    int Counter_ALL = 0, Counter_e =0 ;
    string input = "", temp = "", variables = "";
    string arr[30];
    getline(cin, input);
    input += ' ';
    for (int i = 0; i < input.size(); i++) //split array 
    {
        if (input[i] != ' ')
            temp += input[i];
        else
        {
            arr[A] = temp;
            temp = "";
            A += 1;
        }
    }
    temp = "";
    // wrong logic circuit 
    for (int i = 0; i < 30; i++)
    {
        if (arr[i] == "e")
        {
            Counter_e++;
        }
        else if (arr[i] == "XOR" || arr[i] == "OR" || arr[i] == "NOR" || arr[i] == "NOT" || arr[i] == "NAND" || arr[i] == "AND")
        {
            Counter_ALL++;
        }
    }

    if (Counter_ALL != Counter_e || Counter_ALL == 0)
    {
        cout << "Wrong Logic Circuit Description";
        return 0;
    }

    for (int i = 0; i < 30; i++)
    {

        if (arr[i].size() > 1 && arr[i] != "XOR" && arr[i] != "OR" && arr[i] != "NOR" && arr[i] != "NAND" && arr[i] != "AND" && arr[i] != "NOT")
        {
            cout << "Wrong Logic Circuit Description"; 
            return 0;
        }
    }

    for (int i = 0; i < 30; i++) // counter of variables
    {
        if (arr[i] != "XOR" && arr[i] != "OR" && arr[i] != "NOR" && arr[i] != "NAND" && arr[i] != "AND" && arr[i] != "NOT" && arr[i] != "1" && arr[i] != "0" && arr[i] != "" && arr[i] != "e")
        {
            if (search(arr[i][0], variables)) 
            {
                counter_of_variables += 1;
                variables += arr[i];
            }
        }
    }

    variables = "";

    for (int i = 0; i < 30; i++) // invalid input 
    {
        if (arr[i] == "e")
        {
            if (arr[i - 1] == "NOT" || arr[i - 1] == "XOR" || arr[i - 1] == "OR" || arr[i - 1] == "NOR" || arr[i - 1] == "NAND" || arr[i - 1] == "AND")
            {
                cout << "result : BAD input : missing input number";
                return 0;
            }
        else if ( arr[i-1].size() == 1 )
            {
                if (arr[i - 2] == "XOR" || arr[i - 2] == "OR" || arr[i - 2] == "NOR" || arr[i - 2] == "NAND" || arr[i - 2] == "AND")
                {
                    cout << "result : BAD input : missing input number";
                    return 0;
                }
            }
        }
    }

    if (counter_of_variables > 0) // missing variables
    {
        cout << counter_of_variables << " varaibles are missing please enter them in separate lines" << endl;
        for (int i = 0; i < 30; i++)
        {
            if (arr[i] != "XOR" && arr[i] != "OR" && arr[i] != "NOR" && arr[i] != "NAND" && arr[i] != "AND" && arr[i] != "NOT" && arr[i] != "1" && arr[i] != "0" && arr[i] != "" && arr[i] != "e")
            {
                cin >> temp;
                V_to_C(temp[temp.size() - 1], arr[i][0], arr);

            }
        }
    }

    sort(arr, 30);
    for (int j = 30; j >= 0; j--) // functions
    {
        if (arr[j] == "XOR")
        {
            arr[j] = XOR(arr[j + 1], arr[j + 2]);
            arr[j + 1] = 'e';
            arr[j + 2] = 'e';
            sort(arr, 30);
            counter_XOR += 1;
        }
        else if (arr[j] == "OR")
        {
            arr[j] = OR(arr[j + 1], arr[j + 2]);
            arr[j + 1] = 'e';
            arr[j + 2] = 'e';
            sort(arr, 30);
            counter_OR += 1;
        }
        else if (arr[j] == "NOT")
        {
            arr[j] = NOT(arr[j + 1]);
            arr[j + 1] = "e";
            sort(arr, 30);
            counter_NOT += 1;
        }
        else if (arr[j] == "NOR")
        {
            arr[j] = NOR(arr[j + 1], arr[j + 2]);
            arr[j + 1] = 'e';
            arr[j + 2] = 'e';
            sort(arr, 30);
            counter_NOR += 1;
        }
        else if (arr[j] == "NAND")
        {
            arr[j] = NAND(arr[j + 1], arr[j + 2]);
            arr[j + 1] = 'e';
            arr[j + 2] = 'e';
            sort(arr, 30);
            counter_NAND += 1;
        }
        if (arr[j] == "AND")
        {
            arr[j] = AND(arr[j + 1], arr[j + 2]);
            arr[j + 1] = 'e';
            arr[j + 2] = 'e';
            sort(arr, 30);
            counter_AND += 1;
        }
    }
  cout << "AND gates : " << counter_AND << endl;
  cout << "OR gates : " << counter_OR << endl;
  cout << "NOT gates : " << counter_NOT << endl;
  cout << "XOR gates : " << counter_XOR << endl;
  cout << "NAND gates : " << counter_NAND << endl;
  cout << "NOR gates : " << counter_NOR << endl;
  cout << "result : " << arr[0];
}