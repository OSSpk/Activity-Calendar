#include <iostream>
#include <cstdlib>
#include <fstream>
#include <windows.h>

using namespace std;

//Some Global Constants
const int MONTHS = 12;
const int DAYS = 31;
const int HOURS = 24;
const int BUF_SIZE = 100;

/*Some COLOR Constants*/
const int RED = 12;
const int PURPLE = 13;
const int GREEN = 10;
const int AQUA = 11;
const int YELLOW = 14;
const int WHITE = 15;
const int BLUE = 9;


//Prototypes of Functions

void Calendar_2016();
void Calendar_Initialization (char**** &Calendar);
int  Print_Menu();
void Load_Activities_from_file (char **** &Calendar , int TotalDays[]);
void Point_Activity (char *buffer, char**** &Calendar , int TotalDays[]);
void return_Date_Month_Hour (char* buffer, int &date, int &month, int &hr);
void ViewAllActivities (char ****Calendar , int TotalDays[]);
void changeIndex_to_Month_Name (char *month_Name,int index);
void ViewActivities_by_MONTH (char ****Calendar , int TotalDays[]);
void change_monthName_to_Index (char *month_Name , int &index);
void ViewActivities_by_DAY (char ****Calendar , int TotalDays[]);
void Add_NewActivity (char **** &Calendar , int TotalDays[]);
void Replace_Activity (char* buffer , char**** Calendar , bool& replace);
void Remove_an_Activity (char ****Calendar , int TotalDays[]);
void Save_Activities_in_file (char ****Calendar, int TotalDays[]);
void de_allocate_Calendar(char**** &Calendar , int TotalDays[]);
void color(int k);
void Copy_String (char* source , char* destination );



void color(int k)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}



void  Copy_String (char destination[], char source[]  )
{
	int i = 0;
         for (i = 0 ; source[i]!= '\0' ;i++)
         {
            destination[i] = source[i];
         }

   destination[i] = '\0';
}


void de_allocate_Calendar(char**** &Calendar , int TotalDays[])
{
	if (Calendar != NULL)
	{
	 	for (int i = 0; i < MONTHS; ++i)
	 	{
	 			if (Calendar[i]!= NULL)
	 			{
	 				for (int j = 0; j < TotalDays[i]; ++j)
	 				{
	 					if (Calendar[i][j] != NULL)
	 					{
	 							for (int k = 0; k < HOURS; ++k)
	 							{
	 								if (Calendar[i][j][k] != NULL)
	 								{
	 									delete[] Calendar [i][j][k];
	 									Calendar[i][j][k] = NULL;
	 								}
	 							}

	 						delete[] Calendar[i][j];
	 						Calendar [i][j] = NULL;
	 					}
	 				}

	 				delete[] Calendar[i];
	 				Calendar[i] = NULL;
	 			}
	 	}
	  	delete[] Calendar;
	 	Calendar = NULL;
   }	
}



void Save_Activities_in_file (char ****Calendar , int TotalDays[])
{
	/*self explanatory*/

	ofstream source("ActivityLog.txt");
	if(source.is_open())
	{ 
		if (Calendar!= NULL)
		{
			for(int i = 0; i < MONTHS;i++)
			{
				if (Calendar[i] != NULL)
				{
					for (int j = 0; j < TotalDays[i]; ++j)
					{

						if (Calendar[i][j] != NULL)
						{
							for (int k = 0; k < HOURS; ++k)
							{
								if (Calendar[i][j][k] != NULL)
								{
									source << Calendar[i][j][k]<<endl;
								}
							}
						}
					
					}
				}
			
			}
		}
		
		source.close();
		cout<<"\nActivities saved succesfully in the File.";
	}
	else
	{
		cout<<"Could not open file.";
	}
}





void Remove_an_Activity (char ****Calendar , int TotalDays[])
{
	char confirm = 0;
	char buffer[BUF_SIZE] = {};;
	int  date    = 0;
	int  month   = 0;
	int  hr      = 0;

	cout<<"Enter Information of Activity which you want to delete :\n";
	
	cout<<"Enter DAY in the format \"dd mm yyyy\":";
    cin.ignore ();
	cin.getline (buffer,BUF_SIZE);

	/* Check for Invalid Input */
	while ( strlen(buffer)!= 10)
	{
        cout<<"\n--------INVALID Format--------\n";
        cout<<"\nCorrect Format is \"dd mm yyyy\"\n";
        cout<<"Enter the DAY : ";
        cin.getline (buffer , BUF_SIZE);
	}

	int size = strlen(buffer);
	buffer[size] = ' ';

	cout<<"Enter HOUR in the format \"HH:MM\" or \"H:MM\" :" ;

	cin.getline (buffer + size + 1 , BUF_SIZE);

	return_Date_Month_Hour (buffer, date, month, hr); // takes char[] and returns date, month and hour after parsing.

    if(month < 13 && date < TotalDays[month-1] && hr < 24)
    {	
		if (Calendar != NULL)
		{
			if (Calendar[month -1] != NULL)
			{
				if (Calendar[month-1][date-1] != NULL)
				{
					if (Calendar[month - 1][date - 1][hr] != NULL)
					{
						cout << "Are you sure you want to delete the Activity \"";
						color(RED);
						cout<<(Calendar[month - 1][date - 1][hr] + 16)<<"\"";
						color(WHITE);
						cout<<" (Y/N)\n";
			
						cin  >> confirm;
	
						if(confirm == 'Y' || confirm =='y')
						{
							delete[] Calendar[month - 1][date - 1][hr];

							Calendar[month - 1][date - 1][hr] = nullptr; // NULLED!! So that there will be no issue in the future.
							cout<<"\nActivity Removed Succesfully.";
						}
						else if(confirm == 'n' || confirm == 'N')
						{			
							cout<<"\nActivity was NOT Removed.";
						}
					}

				}
			}
		}
	}

  	else
	{
		cout<<"\nThis Activity does not Exist . \n";
	}
}





void Replace_Activity (char* buffer , char**** Calendar , bool& replace)
{
  	int index 	  = 0;
	int date  	  = 0;
	int month 	  = 0;
	int hr    	  = 0;
	char confirm  = 0;

	return_Date_Month_Hour (buffer, date, month, hr); // takes char[] and returns date, month and hour after parsing.
	
	if(month < 13 && date < 32 && hr < 24)
	{
		if (Calendar != NULL)
		{
			if (Calendar[month-1] != NULL && Calendar[month -1][date -1] != NULL)
			{
				if( Calendar[month - 1][date - 1][hr] != NULL )
				{
					cout << "\nThere already exists an activity on this Day and Time i.e \n";
					color(AQUA); 
					cout<< Calendar[month - 1][date - 1][hr];
					color(WHITE);
					cout << "\nDo you really want to replace it ?";
					cout << "\n(Y/N)";
					cin  >> confirm;

					if(confirm == 'Y' || confirm =='y')
					{
						delete[] Calendar[month - 1][date - 1][hr];
    	   	 
						Calendar[month - 1][date - 1][hr] = new char [strlen(buffer) + 1];
						Copy_String ( Calendar[month - 1][date - 1][hr] , buffer );
						replace = TRUE;
						cout << "\nActivity has been replaced succesfully .";
					}

					else
					{	
						cout << "\nThe Activity was not replaced .";
					}	
				}
			}
		}
				
	}
    else
	{
		cout<<"\nYou have Entered Wrong date or invalid time";
	}
 }





void Add_NewActivity (char **** &Calendar , int TotalDays[])
{
	int date = 0; int month = 0; int hr = 0;
	bool replace = FALSE;

	/*taking input 3 times in the same char[] but WITHOUT overwriting. Every new input is concatenated after the previous one.*/

	char buffer[BUF_SIZE] = {};

	cout << "\nEnter DAY in the format \"dd mm yyyy\":";
    cin.ignore ();
	cin.getline (buffer,BUF_SIZE);

	/* Check for Invalid Input */
	while ( strlen(buffer) != 10)
	{
        cout<<"\n--------INVALID Format--------\n";
        cout<<"\nCorrect Format is \"dd mm yyyy\"\n";
        cout<<"Enter the DAY : ";
        cin.getline (buffer , BUF_SIZE);
	}	

	int size = strlen(buffer);

	buffer[size - 5] = '/' ; // puts 'slash' in order to attain the particular date format i.e 11/01/2016
	buffer[size - 8] = '/' ; // puts 'slash' in order to attain the particular date format i.e 11/01/2016
	buffer[size]     = ' ' ;

	cout<<"Enter HOUR in the format \"HH:MM\" or \"H:MM\" :" ;
	cin.getline (buffer + size + 1 , BUF_SIZE);	
	size = strlen(buffer);

	buffer[size] = ' ';
	cout<<"Enter Activity Description :";
	cin.getline (buffer + size + 1,BUF_SIZE);
	
	return_Date_Month_Hour (buffer, date, month, hr);

    
	if(month < 13 && date < TotalDays[month-1] && hr < 24) 
	{
		/*Checks if there exists an activity on the specified day and time
        and if it exists , then prompts the user to replace it or not */ 

        Replace_Activity (buffer , Calendar , replace); 
		if( !replace )
		{	
			Point_Activity (buffer,Calendar,TotalDays); // this function points char[] to particular pointer (Activity)
			cout << "\nActivity has been added Succesfully.\n";
		}
	}

	else
	{
		cout<<"\nYou have Entered Wrong date or invalid time";
	}
}





void ViewActivities_by_DAY (char ****Calendar , int TotalDays[])
{
	bool empty   		= true;
	int  hr      		= 0;
	int  date    		= 0;
	int  month   		= 0;
	char day [BUF_SIZE] = {};

	cout << "\nEnter the DAY in the format 'dd mm yyyy' : ";

	cin.ignore ();
	cin.getline ( day , BUF_SIZE );

    /* Check for Invalid Input */
	while ( strlen(day)!= 10)
	{
        cout<<"\n--------INVALID Format--------\n";
        cout<<"\nCorrect Format is \"dd mm yyyy\"\n";
        cout<<"Enter the DAY : ";
        cin.getline (day , BUF_SIZE);
	}	

	return_Date_Month_Hour ( day, date, month, hr); // takes char[] and returns date, month and hour after parsing.
	cout << "\n";
	color(BLUE);
	cout<<"Activities : \n";
	color(WHITE);
	
	if(month < 13 && date < TotalDays[month-1] && hr<24)
	{
		if (Calendar != NULL)
		{
			if (Calendar[month-1] != NULL)
		    {
		  		if (Calendar[month-1][date-1] != NULL)
		  		{
		  			for (int k = 0; k < HOURS; ++k)
					{
						if (Calendar[month-1][date-1][k])
						{
						  	empty = false; // that particular pointer is not null so empty = false
							cout << ( Calendar[month - 1][date - 1][k]  + 11) << endl; 
	   					}
	   				}	
		  		}
		  	}	
		}
		
							      
		if(empty)
		{
			cout<<"\nYOU HAVE NO ACTIVITIES ON ";
				color(PURPLE);
				cout << day << endl;
				color(WHITE);
		}

	}
	else
	{
		cout<<"\nYou entered wrong Date or invalid Time.\n";
	}

}





void change_monthName_to_Index (char *month_Name , int &index)
{
	if 		(strcmp(month_Name,"January") 	== 0 || strcmp(month_Name,"january") == 0)
		index = 0;
	
	else if (strcmp(month_Name,"February") 	== 0 || strcmp(month_Name,"february") == 0)
		index = 1;
	
	else if (strcmp(month_Name,"March") 	== 0 || strcmp(month_Name,"march") == 0)
		index = 2;
	
	else if (strcmp(month_Name,"April") 	== 0 || strcmp(month_Name,"april")  == 0)
		index = 3;

	else if (strcmp(month_Name,"May")		== 0 || strcmp(month_Name,"may") == 0)
		index = 4;
	
	else if (strcmp(month_Name,"June")  	== 0 || strcmp(month_Name,"june") == 0)
		index = 5;
	
	else if (strcmp(month_Name,"July")  	== 0 || strcmp(month_Name,"july") == 0)
		index = 6;
	
	else if (strcmp(month_Name,"August") 	== 0 || strcmp(month_Name,"august") == 0)
		index = 7;

	else if (strcmp(month_Name,"September") == 0 || strcmp(month_Name,"september") == 0)
		index = 8;
	
	else if (strcmp(month_Name,"October") 	== 0 || strcmp(month_Name,"october") == 0)
		index = 9;

	else if (strcmp(month_Name,"November") 	== 0 || strcmp(month_Name,"november") == 0)
		index = 10;

	else if (strcmp(month_Name,"December") 	== 0 || strcmp(month_Name,"december") == 0)
		index = 11;

}





void ViewActivities_by_MONTH (char ****Calendar , int TotalDays[])
{
	bool empty          = true;
	int  index          = -1;
	char month_Name [BUF_SIZE] = {};

	cout << "\nEnter Month :";
	cin.ignore ();
	cin.getline (month_Name , BUF_SIZE);

	change_monthName_to_Index (month_Name , index); // takes Month's Name and returns corresponding index

	while (index == -1)
	{
		cout<<"\n----Invalid Month Name----\n";
		cout << "\nEnter Month :";
		cin.getline (month_Name , BUF_SIZE);
		change_monthName_to_Index (month_Name , index); // takes Month's Name and returns corresponding index	
	}


		cout <<endl;
		color(GREEN);
		cout << month_Name << ":\n";
		color(WHITE);

 	if( Calendar != NULL)
 	{	
 		if (Calendar[index] != NULL)
 		{
			for (int j = 0; j < TotalDays[index]; ++j)
			{
					if (Calendar[index][j] != NULL)
					{
						for (int k = 0; k < HOURS; ++k)
						{
							if (Calendar[index][j][k])
							{
							  	empty = false; // that particular pointer is not null so empty = false
								cout << Calendar[index][j][k] << endl;
							}
						}	
					}
	
			}
		}
	}	

    /* if there are no activities than print this*/
	if (empty) 
	{
		cout<<"\nYOU HAVE NO ACTIVITIES IN "<< month_Name <<endl ;
	}	

}



/* corresonding month's name for a particular index */
void changeIndex_to_Month_Name (char *month_Name, int index) 
{
	switch(index) 
	{
		/* putting the corresponding month's name according to index*/
		case 0:
		Copy_String(month_Name,"January"); // 0 is the value of index
		break;
        
        /* when index == 1 then it copies February into month_Name and so on..*/
		case 1:
		Copy_String(month_Name,"February"); 
		break;

		case 2:
		Copy_String(month_Name,"March");
		break;

		case 3:
		Copy_String(month_Name,"April");
		break;

		case 4:
		Copy_String(month_Name,"May");
		break;

		case 5:
		Copy_String(month_Name,"June");
		break;

		case 6:
		Copy_String(month_Name,"July");
		break;

		case 7:
		Copy_String(month_Name,"August");
		break;

		case 8:
		Copy_String(month_Name,"September");
		break;

		case 9:
		Copy_String(month_Name,"October");
		break;

		case 10:
		Copy_String(month_Name,"November");
		break;

		case 11:
		Copy_String(month_Name,"December");
		break;

		default:;
	}
}





void ViewAllActivities (char ****Calendar , int TotalDays[])
{
	bool empty          = true;
	bool flag           = true;
	char month_Name[10] = {};

	if (Calendar != NULL)
	{
		for (int i = 0; i < MONTHS; ++i)
		{
			if (Calendar[i]!= NULL)
			{
			  flag = true;
			  changeIndex_to_Month_Name ( month_Name ,i );// takes a particular index and returns the corresponding month's name in the string 'month_Name'

				for (int j = 0; j < TotalDays[i]; ++j)
				{
					if (Calendar[i][j] != NULL)
					{
						for (int k = 0; k < HOURS; ++k)
						{
							if (Calendar[i][j][k])
							{
							  	empty = false; // that particular pointer is not null so empty = false

								if(flag)
								{
									cout << endl;
									color(240);
									cout << month_Name << ":\n";
									color(WHITE); // so that all activities of the same month get printed under it.
									flag = false;
								}

								cout << Calendar[i][j][k] << endl;
							}
						}	
					}
			
				}
			}
		
		}


	}
	
	if (empty) // if there are no activities than print this
	{
		cout << "\nTHERE ARE NO ACTIVITIES IN THE CALENDAR.\n" ;
	}

}





/* takes char[] and returns date, month and hour after parsing.*/
void return_Date_Month_Hour (char* buffer, int &date, int &month, int &hr) 
{
	  /*Tokenization*/
	 date  = ((buffer[0] - 48) * 10) + (buffer[1] - 48); 
	 month = ((buffer[3] - 48) * 10) + (buffer[4] - 48); 

	 int i = 10;

		/* if HOURS < 10 then store 11th index to hr (by first converting it to an integer)*/ 
		if (buffer[i + 2] == ':')
		{
			hr = buffer[i + 1] - 48; 
		}

        /* if HOURS > 10 then store the Whole (two digits) Number to hr (by first converting it to an integer)*/
		else if (buffer[i + 3] == ':')
		{
			hr = ((buffer[i + 1] - 48) * 10) + (buffer[i + 2] - 48);
		}
}





void Point_Activity (char *buffer, char**** &Calendar , int TotalDays[]) // this function points char[] to particular pointer (Activity)
{
	int index = 0;
	int date  = 0;
	int month = 0;
	int hr    = 0;

	return_Date_Month_Hour (buffer, date, month, hr); // takes char[] and returns date, month and hour after parsing.
    
	if(Calendar == NULL)
    {		
		Calendar = new char*** [MONTHS];
			for (int i = 0; i < MONTHS; ++i)
			{
				Calendar[i] = NULL;
			}
	}

	if (Calendar [month - 1] == NULL)
	{

		Calendar[month - 1] = new char** [TotalDays[month-1]];
		 	for (int i = 0; i < TotalDays[month-1] ; ++i)
	 	 	{
		 		Calendar[month-1][i] = NULL;	
		 	}
    }
	
	if (Calendar [month - 1][date - 1] == NULL)
	{
        Calendar[month-1][date-1] = new char* [HOURS];
       		for (int i = 0; i < HOURS; ++i)
       		{
       		  Calendar[month -1][date-1][i] = NULL;
       		}
	}

    if ( Calendar [month-1][date-1][hr] == NULL)
    {
           Calendar[month - 1][date - 1][hr] = new char [strlen(buffer) + 1];
           Copy_String ( Calendar[month - 1][date - 1][hr] , buffer );
    }
}





void Load_Activities_from_file (char **** &Calendar , int TotalDays[])
{
	char buffer[BUF_SIZE] = {};

	ifstream source ("ActivityLog.txt");

	if( source.is_open() )
	{
		while( source.getline(buffer,BUF_SIZE) )
		{
			Point_Activity(buffer,Calendar , TotalDays); // this function points char[] to particular pointer (Activity)
		}

		source.close();
		cout << "\nAll Activities are loaded succesfully. \n";
	}
	else
	{
		cout<<"Could not open file.";
	}
}





int Print_Menu()
{
	int x = 0;

    /**************** MENU with some formatting  **********/
    color(RED);
    cout<<"\n\n\n\t---------------------------------------------------------\n";
    color(AQUA);
	cout<<"\t|		 Welcome to Calendar 2016		|\n";
	color(RED);
	cout<<"\t---------------------------------------------------------\n";
	color(GREEN);							
	cout<<"\t|	Please choose from the following options :      |\n";
	color(YELLOW);
	cout<<"\t|	                                                |\n";
	cout<<"\t|	 ";
	color(PURPLE);
	cout<<"1-";
	color(YELLOW);
	cout<<"	View All Activities	 	 	|\n";
	cout<<"\t|	 ";
	color(PURPLE);
	cout<<"2-";
	color(YELLOW);
	cout<<"	View Activities by MONTH	 	|\n";
	cout<<"\t|	 ";
	color(PURPLE);
	cout<<"3-";
	color(YELLOW);
	cout<<"	View Activities by DAY	 	 	|\n";
	cout<<"\t|	 ";
	color(PURPLE);
	cout<<"4-";
	color(YELLOW);
	cout<<"	Add New Activity	 	 	|\n";
	cout<<"\t|	 ";
	color(PURPLE);
	cout<<"5-";
	color(YELLOW);
	cout<<"	Remove an Activity	 	 	|\n";
	cout<<"\t|	 ";
	color(PURPLE);
	cout<<"6-";
	color(YELLOW);
	cout<<"	Load Activities from file	 	|\n";
	cout<<"\t|	 ";
	color(PURPLE);
	cout<<"7-";
	color(YELLOW);
	cout<<"	Save Activities in file	 	 	|\n";
	cout<<"\t|	 ";
	color(PURPLE);
	cout<<"8-";
	color(YELLOW);
	cout<<"	Exit	 	 		 	|\n";
	cout<<"\t|_______________________________________________________|\n";
	color(WHITE);
	cout<<"\t\nOption : ";
	    
	cin >> x;


	return x;
}





void Calendar_2016()
{
	int userInput = 0;
	char ****Calendar = NULL;
	int TotalDays[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

	//Calendar_Initialization (Calendar);

	do
	{
		userInput = Print_Menu(); // 'break;' is allowed in switch structure ( I asked Ma'am Samin )

		switch(userInput)
		{

    	case 1:
		ViewAllActivities(Calendar , TotalDays);
    	break;

    	case 2:
    	ViewActivities_by_MONTH(Calendar , TotalDays);
    	break;

    	case 3:
    	ViewActivities_by_DAY(Calendar , TotalDays);
    	break;

    	case 4:
    	Add_NewActivity(Calendar, TotalDays);
    	break;

    	case 5:
    	Remove_an_Activity(Calendar ,TotalDays);
    	break;

    	case 6:
    	Load_Activities_from_file(Calendar , TotalDays);
    	break;

    	case 7:
    	Save_Activities_in_file(Calendar, TotalDays);
    	break;

		case 8:
		break;

    	default :
    	cout << "---Invalid Entry--- \nPlease choose from the Options below.\n ";

    	}

	} while(userInput != 8);


    cout << "Exiting ...........\n";
	de_allocate_Calendar(Calendar , TotalDays);
}



int main()
{
	Calendar_2016();
	system("PAUSE");
	return 0;
}

