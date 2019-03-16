#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>

using namespace std;

class stackType
{
public:
	void initializeStack();

	bool isEmptyStack() const;

	bool isFullStack() const;

	void push(const double newItem);

	void pop();

	int stackTopReturn();

	double top() const;


	stackType(int stackSize);

	~stackType();

private:
	int maxStackSize;
	int stackTop;
	double *list;


};

void findNumberDif(double *row, int count, double* listDif, int &countDif); 
void mergeSort(double *row, double *column,double*value, int first, int last,double* merRow,double* merCol,double*merValue,int &countComparison);
void merge(double* row,double* column,double*value,double* merRow,double* merCol,double*merValue, int first,int last,int mid,int &countComparison);
int minLocation(double *row, double* column,int first, int last,int &countComparison);
void swap(double *row, double*column, double*value, int first, int second);
void selectionSort(double*row, double*column, double*value, int count, int &countComparison);
void eliminateZero(double* listDif, double *numberOfLine, int count);
int checkSort(double*row,double* column, int count);
void sort(double *numberOfLine, int countDif);
double mulMatrix(double row, double column, int countA, int countB, double *rowA
			   ,double *columnA,double *valueA,double *rowB, double *columnB, double *valueB);
double mulMatrixbinary(double column, int countB,double columnA,double *rowB, double *columnB, double *valueB);
void bigO(int count,int countComparison,ofstream &output);
void rechability(double *numberOfLine, int countB,double columnA,double *rowB, double *columnB, double *valueB,int interator,double *reachVertex, int countDifB,int& reachVertexCount,double source,bool *visit);
void DFS (int countB, double source, double *rowB, double *columnB, double *valueB, int interator, double *reachVertex, int &reachVertexCount,double sourceCheck, bool *visit);
void DFSNonRecursive (int countB, double source, double *rowB, double *columnB, double *valueB, double *reachVertex, bool *visit);
int binarySearch(double item, double *iD, int countLabel);




int stackType::stackTopReturn()
{
	return stackTop;
}


void stackType::initializeStack()
{
	stackTop =0;
}

bool stackType::isEmptyStack() const
{
	return(stackTop == 0);
}

bool stackType::isFullStack() const
{
	return (stackTop == maxStackSize);
}

void stackType::push(double newItem)
{
	
		list[stackTop] = newItem;
		stackTop++;
	
}

double stackType::top() const
{

	return list[stackTop-1];
}

void stackType::pop()
{
	if(!isEmptyStack())
		stackTop--;
}

stackType::stackType(int stackSize)
{
	maxStackSize = stackSize;
	stackTop = 0;
	list = new double[maxStackSize];
	
}

stackType::~stackType()
{
	delete [] list ;
}


int main()
{

	int countB =0;
	ifstream inputA ;
	ifstream inputB ;
	ofstream output;
	string line;
	
	int col ;
	double check[3];
	for(int i = 0; i<3 ; i++)
		check[i] = 0;
	double temp =0;
	double sourceCheck = 2;
	double source = sourceCheck;
	int interator = 100100;

	//variable for label file
	string *label;
	double *iD;
	int countLabel=0;

	//variable use for hash table to find connected vertex
	double *rowB;
	double *columnB;
	double *valueB;
	double *merRowB;
	double *merColB;
	double *merValueB;
	double *reachVertex;
	double *result;
	int countDif = 0;
	bool *visit;


	
	double *listDifB;

	double *numberOfLineB;

	int countDifB =0;
	int first =0;
	
	int lastB ;
	int countComparisonA = 0 ;
	int countComparisonB = 0 ;

	inputB.open("l01.txt");
	if(!inputB.eof())
	{
		while(getline(inputB, line))
		{
			if(line.empty() || line.at(0) == '#')
				continue;
			countLabel++;
		}
	}
	inputB.close();

	label = new string [countLabel];
	iD = new double [countLabel];
	for(int i = 0; i < countLabel ; i++)
	{
		label[i] = "";
		iD[i] = 0;
	}

	countLabel =0;
	inputB.open("l01.txt");
	if(!inputB.eof())
	{
		string tempstring ="";
		while(getline(inputB, line))
		{
			if(line.empty() || line.at(0) == '#')
				continue;
			istringstream ss(line);
			while(ss >> temp >> tempstring)
			{
				iD[countLabel] = temp;
				label[countLabel] = tempstring;
			
			}
			countLabel++;
		}
	}
	inputB.close();



	inputB.open("07b.txt");
	if(!inputB.eof())
	{
		while(getline(inputB, line))
		{
			if(line.empty() || line.at(0) == '#')
				continue;
			istringstream ss(line);
			col = 0;
			while(ss >> temp)
			{
				check[col] = temp;
				col++;
			}
			if(check[0] < 1 || check[1] < 1)
			{
				countB--;
			}
			countB++;
		}
	}
	inputB.close();


	rowB = new double [countB];
	columnB = new double[countB];
	valueB = new double[countB];
	listDifB = new double[countB];
	merRowB = new double[countB];
	merColB = new double[countB];
	merValueB = new double[countB];
	reachVertex = new double[countB];
	visit = new bool[countB];
	result = new double[countB];
	for(int  i = 0 ; i < countB ; i++)
	{
		rowB[i] = 0;
		columnB[i] = 0;
		valueB[i] = 0;
		listDifB [i] = 0;
		reachVertex[i] = 0;
		visit[i] = false;
		result[i] = 0;
	}

	countB =0;
	inputB.open("07b.txt");
	if(!inputB.eof())
	{
		while(getline(inputB,line))
		{
			if(line.empty() || line.at(0) == '#')
				continue;
			istringstream ss(line);
			col = 0;
			while (ss >> temp)
			{
				check[col] = temp;
				col++;
			}
			if(check[0] < 1 || check[1] < 1)
			{
				countB--;
			}else
			{
				rowB[countB] = check[0];
				columnB[countB] = check[1];
				valueB[countB] = check[2];
			}
			countB++;
		}
	}

	lastB = countB -1 ;

	mergeSort(rowB,columnB,valueB,first,lastB,merRowB,merColB,merValueB,countComparisonB);

		findNumberDif(columnB,countB,listDifB, countDifB);
		numberOfLineB = new double [countDifB];
		for(int i=0; i<countDifB ;i++)
			numberOfLineB[i] = 0;
	
		eliminateZero(listDifB, numberOfLineB, countB);
		sort(numberOfLineB, countDifB);
		
		



		output.open("out.txt");
		/*reachVertex[0] = source;*/

		
		
		int reachVertexCount =1;
	/*rechability(numberOfLineB,countB,source,rowB,columnB,valueB,interator,reachVertex,countDifB,reachVertexCount, sourceCheck, visit);*/
		/*DFS(countB,source,rowB,columnB,valueB,interator,reachVertex,reachVertexCount,sourceCheck,visit);*/
		/*findNumberDif(reachVertex,reachVertexCount,result,countDif);*/
	

		DFSNonRecursive(countB, source,rowB,columnB,valueB,reachVertex,visit);
			sort(reachVertex, countB);
	for(int i = 0; i <countB; i++)
	{
		if(reachVertex[i] != 0)
		{
			int match = binarySearch(reachVertex[i],iD,countLabel);
			if(match != -1)
			{
			output <<reachVertex[i] << "    "<<label[match] << endl;
			cout << reachVertex[i]  << "    "<<label[match] << endl;
			}
		}
	}
		/*while(!connectedVertex.isEmptyStack())
		{
			cout<< connectedVertex.top() <<endl;
			connectedVertex.pop();
		}*/

		

			delete [] listDifB;
			delete [] numberOfLineB;

	output.close();

	delete [] rowB;
	delete [] columnB;
	delete [] valueB;
	delete [] merColB;
	delete [] merValueB;
	delete [] reachVertex;
	delete [] visit;
	delete [] label;
	delete [] iD;
	system ("pause");

	return 0;
}

void findNumberDif(double *row, int count, double* listDif, int &countDif)
{
	int checkDif=0;
	for(int i = 0; i<count ;i++)
	{
		for(int j=0; j <count; j++)
		{
			if(row[i] != listDif[j])
			{
				checkDif =1;
			} else
			{
				checkDif = 0;
				j = count;
			}
		}
		if(checkDif == 1)
		{
			listDif[i] = row[i];
			countDif++;
		}
	}
}

void mergeSort(double *row, double *column,double*value, int first, int last,double* merRow,double* merCol,double*merValue, int &countComparison)
{
	int mid;
	if(first < last)
	{
		mid =(first + last)/ 2;
		mergeSort(row,column,value,first,mid, merRow,merCol,merValue,countComparison);
		mergeSort(row,column,value,mid+1,last,merRow,merCol,merValue,countComparison);
		merge(row,column,value,merRow,merCol,merValue,first,last,mid,countComparison);
	}
}

void merge(double* row,double* column,double*value,double* merRow,double* merCol,double*merValue, int first,int last,int mid,int &countComparison)
{
	int i, j ,k;
	i = first;
	k= first;
	j=mid+1;

	while(i<= mid && j <= last)
	{
		if(row[i] < row[j])
		{
			merRow[k] = row[i];
			merCol[k] = column[i];
			merValue[k] = value[i];
			k++;
			i++;
		} else if(row[i] == row[j] && column[i] < column[j])
		{
			merRow[k] = row[i];
			merCol[k] = column[i];
			merValue[k] = value[i];
			k++;
			i++;
		}else
		{
			merRow[k] = row[j];
			merCol[k] = column[j];
			merValue[k] = value[j];
			k++;
			j++;
		}
		countComparison++;
	}

	while(i <= mid)
	{
		merRow[k] = row[i];
		merCol[k] = column[i];
		merValue[k] = value[i];
		k++;
		i++;
		countComparison++;
	}

	while(j <= last)
	{
		merRow[k] = row[j];
		merCol[k] = column[j];
		merValue[k] = value[j];
		k++;
		j++;
		countComparison++;
	}

	for(i = 0; i < k; i++)
	{
		row[i] = merRow[i];
		column[i] = merCol[i];
		value[i] = merValue[i];
	}

}

void eliminateZero(double* listDif, double *numberOfLine, int count)
{
	int j = 0;
	for (int i =0; i<count; i++)
	{
		
		if(listDif[i] != 0)
		{
			numberOfLine[j] = listDif[i];
			j++;
		}
	}
}

void sort(double *numberOfLine, int countDif)
{
	double temp=0;
	for(int i =0; i<countDif; i++)
	{
		for (int j = 0; j <countDif -1 ;j++)
		{
			if(numberOfLine[j] > numberOfLine[j + 1])
			{
				temp = numberOfLine[j];
				numberOfLine[j] = numberOfLine[j+1];
				numberOfLine[j+1] = temp;
			}
		}
	}
}


int checkSort(double*row, double *column,int count)
{
	int check =0;
	for(int i=0; i<count-1; i++)
	{
		
		if(row[i+1] < row[i])
		{
			i = count;
			check= 1;
		}else if(row[i+1] == row[i] && column[i+1] < column[i])
		{
			
				i = count;
				check = 1;
			
		}else
		{
			check = 0;
		}
	}
	return check;
}

double mulMatrixbinary(double column, int countB,double columnA,double *rowB, double *columnB, double *valueB)
{
	double temp = 0;
	int first =0;
	int last;
	int mid;
	bool found;
	
		found =false;
		first = 0;
		last = countB -1;
		
		
			while(first <= last && !found)
			{
				mid = (first + last) /2;
				if(columnA == rowB[mid])
				{
					
					if(column == columnB[mid])
					{
						
						found = true;
						temp = temp + 1*valueB[mid];
					}else if(columnB[mid] > column)
					{
						last = mid -1;
					}else 
					{
						first = mid + 1;
					}
				}else if(rowB[mid] > columnA)
				{
					last = mid -1;
				}else
				{
					first = mid+1;
				}
			}
	
	return temp;
}

void rechability(double *numberOfLine, int countB,double columnA,double *rowB, double *columnB, double *valueB,int interator,double *reachVertex, int countDifB,int& reachVertexCount,double source, bool *visit)
{
	int check = 0;
	int temp = interator;
	if(interator == 0)
	{
		
	}else
	{
		for (int i =0; i< countDifB; i++)
		{
			int k = numberOfLine[i];
			interator = temp;
			if( mulMatrixbinary(numberOfLine[i], countB,columnA,rowB, columnB,valueB) == 1 && visit[k-1] == false)
			{
				
					if(numberOfLine[i] != source)
					{
						visit[k-1] = true;
						reachVertex[reachVertexCount] = numberOfLine[i];
						reachVertexCount++;
					}

					if(reachVertexCount == countB)
					{
						interator = 0;
					}else
					{
						rechability(numberOfLine, countB, numberOfLine[i],rowB,columnB,valueB,interator-1, reachVertex, countDifB,reachVertexCount, source,visit);
					}
			
				
			}
		}
	}
}

void DFS (int countB, double source, double *rowB, double *columnB, double *valueB, int interator, double *reachVertex, int &reachVertexCount,double sourceCheck, bool *visit)
{
	int check = 0;
	int k =0;
	int temp = interator;
	if(interator == 0)
	{

	}else
	{
		for(int i=0;i<countB; i++)
		{
			k = columnB[i];
			interator = temp;
			if(source == rowB[i] && valueB[i] == 1 && visit[k-1] == false)
			{
				
					if(columnB[i] != sourceCheck)
					{
						visit[k-1] = true;
						reachVertex[reachVertexCount] = columnB[i];
						reachVertexCount++;
					}

					if(reachVertexCount == countB)
					{
						interator =0;
					}else
					{
						DFS(countB,columnB[i],rowB,columnB,valueB,interator-1,reachVertex,reachVertexCount,sourceCheck, visit);
					}
				
			}
		}
		

	}
}

void DFSNonRecursive (int countB, double source, double *rowB, double *columnB, double *valueB, double *reachVertex, bool *visit)
{
	stackType stack(rowB[countB-1]);
	stack.push(source);
	bool checkConnection;
	
	int s = source;
	visit[s-1] = true;
	int k =0;
	while(!stack.isEmptyStack() )
	{
		checkConnection = false;
		if(stack.top() == s)
		{
			stack.pop();
		}
		for(int i =0; i<countB; i++)
		{
			int k = columnB[i];
			if(source == rowB[i] && visit[k-1] ==false && valueB[i] == 1)
			{
				stack.push(columnB[i]);
				
				visit[k-1] = true;
				checkConnection = true;
			}
		}
		if(checkConnection == false)
		{
			reachVertex[k] = stack.top();
			k++;
			stack.pop();
		}
		source = stack.top();
	}
}

int binarySearch(double item, double *iD, int countLabel)
{
	int  first = 0;
	int last = countLabel -1;
	int mid;

	bool found = false;

	while (first <=last && !found)
	{
		mid = (first + last) /2;

		if(iD[mid] == item)
			found = true;
		else if(iD[mid] > item)
			last=mid -1;
		else
			first = mid +1;

	}

	if(found)
		return mid;
	else
		return -1;
}