#pragma once

int Str_Len(char* worb){
	int long_of_worb = 0;
	while(worb[long_of_worb]){
		long_of_worb++;
	}
	return long_of_worb;
}

int Pow_Int(int x, int y){
    if(y == 0)
        return 1;
    int i;
    int c = x;
    for(i = 1; i < y; i++)
        x *= c;
    return x;
}

int Up_to_int(char* str){
    int i, j, count;
    int result = 0;
    count = 0;
    char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for(i = Str_Len(str) - 1; i >= 0; i--){
    	for(j = 1; j < 10; j++)
    		if(str[count] == digits[j]){
    			result = result + j * Pow_Int(10, i);
    			break;
			}
        count++;
    }
    return result;
}

int getNumbers(int* array, std::string Expr){
	int arrayNumber, strPosition;
	arrayNumber = strPosition = 0;
	char numberString[100];
	for(int i = 0; i <= (int)Expr.size(); i++){
		if(Expr[i] != ' ' && Expr[i] != '\n' && Expr[i]){
			numberString[strPosition] = Expr[i];
			strPosition++;
		}
		else{
			numberString[strPosition] = '\0';
			array[arrayNumber] = Up_to_int(numberString);
			arrayNumber++;
			strPosition = 0;
		}
	}
	return arrayNumber;
}
