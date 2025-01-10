#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 300


/////////////////////////////////////////////////////////////////////////////////////

// Functions that keep answers organized

void divider() {

    printf("\n________________________________________\n");
  
}

void stars() {

printf("\n\n**************************************************************************");
  
}


////////////////////////////////////////////////////////////////////////////////////


// removes quotations from string token
void removeChar(char *string, char remove){
  
    int i, j;
    int num = strlen(string);
  
      for(i = 0; i < num; i++) {
        
          if(string[i] == remove) {
            
              for(j = i; j < num; j++) {
                
                  string[j] = string[j + 1];
                
              }
            
              num--;
              i--;
            
          }
        
      }
  
}


//////////////////////////////////////////////////////////////////////////////////////


// Finds the average for each age group for a given province
void ageavg(char prov[], char age[], double percent[], char p, FILE *printto) {

double count, avg, sum = 0, pavgs[4];
char d[4] = {'3', '5', '6', '\0'};
char *agroups[4] = {"35 to 49", "50 to 64", "65+\t\t", "\0"};
char *ag[4] = {"35-49", "50-64", "65+\t\t", "\0"};
int i, j = 0;


  // Determines all the percent values of the province that is being looked at, finds the average for each age group of the province, and adds these values to an array (pavgs[])
  for (j = 0; d[j] != '\0'; j++) {

    count = 0;
    sum = 0;
    
    for (i = 0; prov[i] != '\0'; i++) {
  
        if (prov[i] == p) {
  
            if (age[i] == d[j]) {
    
                if (percent[i] != 0) {
                
                  sum += percent[i];
                  count++;
        
                }
   
            }
    
        }
  
    }

    pavgs[j] = sum / count;
    
  }

  pavgs[j] = '\0';


  
  // Prints the averages in organized columns within the console and prints to its own separate file if the averages relate to the national averages of each age group (Canada (excluding territories))
  printf("\n\nAge Group (years):\t\t\tPercent (%):\n------------------\t\t\t------------\n");  

  if (p == 'C') {
    
      fprintf(printto, "Age Group (years):\t\t\tPercent (%):\n");

  }

  for (i = 0; pavgs[i] != '\0'; i++) {
  
      printf("\n%s\t\t\t\t\t%.2lf", agroups[i], pavgs[i]);
    
        if (p == 'C') {

          if (ag[i] != "65+\t\t") {
          
            fprintf(printto, "%s\t\t\t\t\t\t\t\t\t\t%.2lf\n", ag[i], pavgs[i]);
            
          } else {

            fprintf(printto, "%s\t\t\t\t\t\t\t\t\t%.2lf", ag[i], pavgs[i]);
            
          }
            
        }
      
  }
  
}




/////////////////////////////////////////////////////////////////////////////////////


// Finds the average for each year for a given province
double avgyear(char prov[], int date[], double percent[], char p, double *smallest, int *sm, int *lg, double alldata[8]) {

double count, avg, sum = 0, pavgs[MAX_ROWS], largest = 0;
int y[8] = {2015, 2016, 2017, 2018, 2019, 2020, 2021, '\0'};
int i, j = 0;
*smallest = 100;


  // Determines all the percent values of province that is being looked at, finds the average for each year of the province, and adds these values to an array (pavgs[])
  for (j = 0; y[j] != '\0'; j++) {

    count = 0;
    sum = 0;
    
    for (i = 0; prov[i] != '\0'; i++) {
  
        if (prov[i] == p) {
  
            if (date[i] == y[j]) {
    
                if (percent[i] != 0) {
                
                  sum += percent[i];
                  count++;
        
                }
   
            }
    
        }
  
    }

    pavgs[j] = sum / count;
    alldata[j] = pavgs[j];
    
  }


  pavgs[j] = '\0';
  alldata[j] = '\0';

  


  // Prints the averages in organized columns within the console and to its own separate file
  // Also finds the largest and lowest average for each province
  printf("\n\nYear:\t\t\tPercent (%):\n-----\t\t\t------------\n");  

  

  for (i = 0; pavgs[i] != '\0'; i++) {

      if (pavgs[i] > largest) {

        largest = pavgs[i];
        *lg = i;
        
      }

    if (pavgs[i] < *smallest) {

        *smallest = pavgs[i];
        *sm = i;
        
      }

      printf("\n%d\t\t\t%.2lf", y[i], pavgs[i]);
      
  }


  // Returns the largest percent value of the years for the given province
  return (largest);
  
}






/////////////////////////////////////////////////////////////////////////////


// Finds the overall average percent for a given province
double percentavg(char province[], double percent[], char c) {

double avg, sum = 0;
int i, count = 0;

  // Determines all the percent values of province that is being looked at and finds the average of these values
  for (i = 0; province[i] != '\0'; i++) {


      if (province[i] == c) {

        if (percent[i] != 0) {
        
          sum += percent[i];
          count++;
  
        }
  
      }

  }


  
  // Prints out the name of the province along with their respective overall percent value
  switch (c) {

    case 'O':

      avg = sum / count;
      printf("Ontario\t\t\t\t\t%.2lf\n", avg);
      break;

    case 'Q':

      avg = sum / count;
      printf("Quebec\t\t\t\t\t%.2lf\n", avg);
      break;

    case 'B':

      avg = sum / count;
      printf("British Columbia\t\t%.2lf\n", avg);
      break;

    case 'A':

      avg = sum / count;
      printf("Alberta\t\t\t\t\t%.2lf\n", avg);
      break;

    case 'C':

      avg = sum / count;
      printf("\n\n\nNational Average (Excluding Territories):\n\nCountry:\t\t\t\tPercent (%):\n--------\t\t\t\t------------\nCanada\t\t\t\t\t%.2lf\n", avg);
      break;


  }

  
  
  // Returns the average for the given province
  return (avg);

  
}





////////////////////////////////////////////////////////////////////////////


int main() {
  
  // Open the CSV file for reading
  FILE* fp = fopen("statscan_diabetes.csv", "r");

  int years[MAX_ROWS], i = 0;
  double percent[MAX_ROWS];
  char age[MAX_ROWS], gender[MAX_ROWS], province[MAX_ROWS];
  char line[MAX_ROWS];
  char remove = '"';
   

  // To skip the first row of data (titles/names of categories)
  fgets(line, MAX_ROWS, fp);

  // Stores each line of data into an array and keeps reading file until each row is read
  while (fgets(line, MAX_ROWS, fp) != NULL) {

   

    // Split each line into fields using strtok() function
    char* token = strtok(line, ",");
    int field_num = 0;
    
    
          // Stores each token into their respective array (all necessary conversions are done within each case)
          while (token != NULL) {
            
          removeChar(token, remove);
          

              switch (field_num) {
                
                  case 0:  
                    
                    years[i] = atoi(token); 
                    break;
                
                  case 1:  

                    strncpy(&province[i], token, 2);  
                    break;

                  case 3:  

                    strncpy(&age[i], token, 2);
                    break;

                  case 4:  
                    
                    strncpy(&gender[i], token, 2);
                    break;
                
                  case 13:  

                    percent[i] = atof(token);
                    break;

              }
  
           
              // Move to the next field
              token = strtok(NULL, ",");
              field_num++;
            
          }

      
        // Move to the next row of data
        i++;

    
  }

  age[i] = '\0';
  province[i] = '\0';
  gender[i] = '\0';



/////////////////////////////////////////////////////////////////////////////////



// For Question 1 (a & b):
  
stars();
  
double o, q, b, a, c;

// Calls the percentavg function to find, print, and store each province's percent average into their own respective variables
printf("\n\n\n\nQuestion 1 (a & b):\n\n\nDiabetes Averages (For All Years and Age Groups)\n\nProvince:\t\t\t\tPercent (%):\n---------\t\t\t\t------------\n");
  for (i = 0; i < 5; i++) {

      switch(i) {

        case 0: o = percentavg(province, percent, 'O'); break;
        case 1: q = percentavg(province, percent, 'Q'); break;
        case 2: b = percentavg(province, percent, 'B'); break;
        case 3: a = percentavg(province, percent, 'A'); break;
        case 4: c = percentavg(province, percent, 'C'); break;

        
    }

    
  }

  printf("\n");

//////////////////////////////////////////////////////////////////////////////////
  

// For Question 2:
  
// Stores all overall averages found in Question 1a into an array (allavgs[])
double allavgs[6] = {o, q, b, a, '\0'};
double low = 100, high = 0;
char *namelow, *namehigh;

  // Determines which of the overall averages has the highest and lowest values
  for (i = 0; allavgs[i] != '\0'; i++) {

      if (low > allavgs[i]){
        
          low = allavgs[i];

          switch (i){
            
            case (0): namelow = "Ontario"; break;
            case (1): namelow = "Quebec"; break;
            case (2): namelow = "British Columbia"; break;
            case (3): namelow = "Alberta"; break;
            
          }
        
      }

      if (high < allavgs[i]){
        
          high = allavgs[i];

          switch (i){
            
            case (0): namehigh = "Ontario"; break;
            case (1): namehigh = "Quebec"; break;
            case (2): namehigh = "British Columbia"; break;
            case (3): namehigh = "Alberta"; break;
            
          }
        
      }
    
  }


  // Prints the overall averages that have the highest and lowest values and the names of their respective provinces
  divider();
  printf("\n\n\nQuestion 2:\n");

  printf("\n\nThe province with the highest diabetes percentage (all years and age groups included) is %s with a percentage of %.2lf %\n\nThe province with the lowest diabetes percentage (all years and age groups included) is %s with a percentage of %.2lf %\n\n", namehigh, high, namelow, low);


  
/////////////////////////////////////////////////////////////////////////////////////




  
// For Question 3:

  
  // Determines which overall averages are below the national average and displays them in the console
  divider();
  printf("\n\n\nQuestion 3:\n\n\nProvinces Below National Average\n--------------------------------");
    for (i = 0; allavgs[i] != '\0'; i++) {
  
        if (c > allavgs[i]) {
          
            switch (i) {
              
              case (0): printf("\nOntario"); break;
              case (1): printf("\nQuebec"); break;
              case (2): printf("\nBritish Columbia"); break;
              case (3): printf("\nAlberta"); break;
              
            }
          
        }
      
    }


  // Determines which overall averages are above the national average and displays them in the console
  printf("\n\n\nProvinces Above National Average\n--------------------------------");
    for (i = 0; allavgs[i] != '\0'; i++) {


      if (c < allavgs[i]) {

          switch (i) {
            
            case (0): printf("\nOntario"); break;
            case (1): printf("\nQuebec"); break;
            case (2): printf("\nBritish Columbia"); break;
            case (3): printf("\nAlberta"); break;
            
          }
        
      }
    
  }

  printf("\n\n");
  divider();

  



//////////////////////////////////////////////////////////////////////////////////////


  

// For Question 1 (c):

  
// Opens a file for each province to store their respective yearly averages
FILE* yearresults = fopen("All Yearly Average Percentages", "w");

double onty[8], qbcy[8], bcy[8], alby[8], cany[8];
int yearnum[8] = {2015, 2016, 2017, 2018, 2019, 2020, 2021, '\0'};

double highyear[6], smallyear[6];
int small[6], large[6];

i = 0;

  
  
printf("\n");
stars();


  // Calls the avgyear function to find the yearly averages for each of the provinces and prints them out both the console and their own respective files
  // Also finds the highest and lowest values of each province and stores them into their respective arrays (highyear[] and smallyear[])
  printf("\n\n\n\nQuestion 1c:\n\n\nYearly Diabetes Averages For Each Province (All Age Groups Included):\n");

  divider();
  printf("\nNational Averages For Canada (Excluding Territories):");
  highyear[i] = avgyear(province, years, percent, 'C', &smallyear[i], &small[i], &large[i], cany);
  i++;

  divider();
  printf("\nFor Ontario:");
  highyear[i] = avgyear(province, years, percent, 'O', &smallyear[i], &small[i], &large[i], onty);
  i++;

  divider();
  printf("\nFor Quebec:");
  highyear[i] = avgyear(province, years, percent, 'Q', &smallyear[i], &small[i], &large[i], qbcy);
  i++;

  divider();
  printf("\nFor British Columbia:");
  highyear[i] = avgyear(province, years, percent, 'B', &smallyear[i], &small[i], &large[i], bcy);
  i++;

  divider();
  printf("\nFor Alberta:");
  highyear[i] = avgyear(province, years, percent, 'A', &smallyear[i], &small[i], &large[i], alby);
  divider();


  // Prints all yearly percent data into a separate file (All Yearly Average Percentages)
  fprintf(yearresults, "Year\t\tCAN\t\t\tONT\t\t\tQBC\t\t\tBC \t\t\tALB\n");
  for (i = 0; cany[i] != '\0'; i++) {

    fprintf(yearresults, "%d\t\t%.2lf\t\t%.2lf\t\t%.2lf\t\t%.2lf\t\t%.2lf\n", yearnum[i], cany[i], onty[i], qbcy[i], bcy[i], alby[i]);
    
  }

  







////////////////////////////////////////////////////////////////////////////////


// For Question 4

double big = 0, little = 20;
int smol, jumbo, j, k;
highyear[5] = '\0';
smallyear[5] = '\0';
small[5] = '\0';
large[5] = '\0';

stars();

printf("\n\n\n\nQuestion 4:\n\n");
  


// Using the arrays formed in Question 1c (highyear[] and smallyear[]), the highest and lowest values between all the provinces were determined
for (i = 1; highyear[i] != '\0'; i++) {

    if (highyear[i] > big) {

        big = highyear[i];
        jumbo = large[i];
        j = i;
      
    }

    if (smallyear[i] < little) {

        little = smallyear[i];
        smol = small[i];
        k = i;
      
    }
    
}

  // Prints out the highest percent value with its respective year and province
  switch (j) {

    case (1): printf("\nIn the year %d, Ontario has the highest prevalence of diabetes with a percentage of %.2lf %\n", yearnum[jumbo], big); break;
    case (2): printf("\nIn the year %d, Quebec has the highest prevalence of diabetes with a percentage of %.2lf %\n", yearnum[jumbo], big); break;
    case (3): printf("\nIn the year %d, British Columbia has the highest prevalence of diabetes with a percentage of %.2lf %\n", yearnum[jumbo], big); break;
    case (4): printf("\nIn the year %d, Alberta has the highest prevalence of diabetes with a percentage of %.2lf %\n", yearnum[jumbo], big); break;

  }

  divider();
  printf("\n");


  // prints out the lowest percent value with its respective year and province
  switch (k) {

    case (1): printf("\nIn the year %d, Ontario has the lowest prevalence of diabetes with a percentage of %.2lf %\n", yearnum[smol], little); break;
    case (2): printf("\nIn the year %d, Quebec has the lowest prevalence of diabetes with a percentage of %.2lf %\n", yearnum[smol], little); break;
    case (3): printf("\nIn the year %d, British Columbia has the lowest prevalence of diabetes with a percentage of %.2lf %\n", yearnum[smol], little ); break;
    case (4): printf("\nIn the year %d, Alberta has the lowest prevalence of diabetes with a percentage of %.2lf %\n", yearnum[smol], little ); break;

  }




////////////////////////////////////////////////////////////////////////////

// For Question 1 (d):

  
// Opens a file to store the national averages of each age group (Canada (excluding territories))
FILE* canage = fopen("National Averages For Each Age Group", "w");
 
printf("\n");
stars();

  
  printf("\n\n\n\nQuestion 1d:\n\n\nVarious Age Groups Diabetes Averages For Each Province (All Years Included)\n");

  // Calls the ageavg function to find the averages of each age group for each of the provinces and prints them out both the console
  // The national averages for each age group are printed into both the console and its respective file (National Averages For Each Age Group)
  divider();
  printf("\nNational Averages For Canada (excluding territories):");
  ageavg(province, age, percent, 'C', canage);
  
  
  divider();
  printf("\nFor Ontario:");
  ageavg(province, age, percent, 'O', canage);
  

  divider();
  printf("\nFor Quebec:");
  ageavg(province, age, percent, 'Q', canage);
  

  divider();
  printf("\nFor British Columbia:");
  ageavg(province, age, percent, 'B', canage);
  

  divider();
  printf("\nFor Alberta:");
  ageavg(province, age, percent, 'A', canage);
  divider();

 

  
///////////////////////////////////////////////////////////

// Closes all files that were previously declared
fclose(fp);
fclose(yearresults);
fclose(canage);


// Stops the program  
return (0);

}