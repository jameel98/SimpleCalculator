#include <stdio.h>
#include <string.h>

int isNum(char a)
{
    return a >= '0' && a <= '9';
}
int aToInt(char a)
{
    return a - '0';
}

int getDigits(int a)
{
    int digit = 0;
    while (a > 0)
    {
        a = a / 10;
        digit += 1;
    }
    return digit;
}

float performOperation(float num1, float num2, char operator)
{
    if (operator== '+')
    {
        return num1 + num2;
    }
    else if (operator== '-')
    {
        return num1 - num2;
    }
    else if (operator== '/')
    {
        return num1 / num2;
    }
    else if (operator== 'X')
    {
        return num1 * num2;
    }
}

int getParentIndex(char operators[], int i){
    int index = 0;
    while (operators[i] != ')'){
        i++;
    }
    index = i;
    return index;
}

int getNumber(char input[], int i)
{

    int current = 0;
    int counter = 0;

    while (isNum(input[i]))
    {
        if (counter > 0)
        {
            current = current * counter * 10;
            current += aToInt(input[i]);
        }
        else
        {
            current += aToInt(input[i]);
        }
        counter = 1;
        i++;
    }

    return current;
}

int main()
{
    char input[100] = "1+34X(6+56)-3+6X(3+9456)+876-12/100-2+4";
    float nums[100];     // number array
    char operators[100]; // operators array
    int numIndex = 0;
    int operatorIndex = 0;

    // fill arrays
    for (int i = 0; i <= strlen(input); i++)
    {
        char currentChar = input[i];
        if (currentChar == '+' || currentChar == '-' || currentChar == 'X' || currentChar == '/' || currentChar =='(' || currentChar ==')')
        {
            operators[operatorIndex++] = currentChar;
        }
        else if (isNum(currentChar))
        {
            int number = getNumber(input, i);
            nums[numIndex++] = number;
            i += getDigits(number) - 1;
        }
        else
        {
            input[i] = NULL;
            nums[numIndex] = '/0';
            operators[operatorIndex] = NULL;
        }
    }

    // start with parentheses case
    for (int i = 0; i < operatorIndex; i++) {
        if(operators[i] == '('){
            i++;
            int closeParentIndex  = getParentIndex(operators, i);
            for (int m = i; m < closeParentIndex; m++) {
                if (operators[i] == 'X' || operators[i] == '/') {
                    float result = performOperation(nums[i-1], nums[i], operators[i]);
                    nums[i-1] = result;
                    // shift left the arrays
                    for (int j = i; j < numIndex - 1; j++) {
                        nums[j] = nums[j + 1];
                    }

                    for (int k = i; k < operatorIndex - 1; k++) {
                        operators[k] = operators[k + 1];
                    }
                    // len -1 after removing element
                    numIndex--;
                    operatorIndex--;
                    i--;
                }
            } if (operators[i] == '+' || operators[i] == '-') {
                for (int m = i; m < closeParentIndex; m++) {
                    float result = performOperation(nums[i-1], nums[i], operators[i]);
                    nums[i-1] = result;
                    // shift left the arrays
                    for (int j = i; j < numIndex - 1; j++) {
                        nums[j] = nums[j + 1];
                    }
                    for (int k = i; k < operatorIndex - 1; k++) {
                        operators[k] = operators[k + 1];
                    }
                    numIndex--;
                    operatorIndex--;
                    i--;
                }
            }

            for (int s = i; s < operatorIndex-2; s++) {
                operators[s] = operators[s +2];
            }
            // after removing ()
            operatorIndex = operatorIndex-2;
        }
    }

    // mult and div
    for (int i = 0; i < operatorIndex; i++)
    {
        //calculate
        if (operators[i] == 'X' || operators[i] == '/')
        {
            float result = performOperation(nums[i], nums[i + 1], operators[i]);
            nums[i] = result;
            // shift left the arrays
            for (int j = i + 1; j < numIndex - 1; j++)
            {
                nums[j] = nums[j + 1];
            }

            for (int k = i; k < operatorIndex - 1; k++)
            {
                operators[k] = operators[k + 1];
            }
            // len -1 after removing element
            numIndex--;
            operatorIndex--;
            i--;
        }
    }

    // plus minus
    for (int i = 0; i < operatorIndex; i++)
    {
        // calculate
        float result = performOperation(nums[i], nums[i + 1], operators[i]);
        nums[i] = result;
        // shift left the arrays
        for (int j = i + 1; j < numIndex - 1; j++)
        {
            nums[j] = nums[j + 1];
        }

        for (int k = i; k < operatorIndex - 1; k++)
        {
            operators[k] = operators[k + 1];
        }
        numIndex--;
        operatorIndex--;
        i--;
    }

    printf("Result: %f\n", nums[numIndex - 1]);
    return 0;
}