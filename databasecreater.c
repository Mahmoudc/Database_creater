/*
Author: Mahmoud Chahine

Database creater
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
struct Database { //creates The database structure
	char databaseName[50];
	char table[50];
	char view[50];
	char procedures[50];
}; //extra structure for tables that allow you to add columns and datatypes
struct Table {
	char columns[50];
	int datatypes;
	char datatype[50];
	char values[50];
	char nullvalue[50];
	int null;
	char primaryKey[50];
};

void getDatabaseName(FILE *name, FILE *write, struct Database database); //Writes database name into the file
void createTable(FILE *tables, FILE *adding, FILE *columns, struct Database database, struct Table table, int *maxcolumns, int identity); //appends data to include table name, columns and datatypes
void createTemporary(FILE *tables, FILE *adding, FILE *columns, struct Database database, struct Table table, int *maxcolumns, int identity); //creates temporary table
void createGlobal(FILE *tables, FILE *adding, FILE *columns, struct Database database, struct Table table, int *maxcolumns, int identity); //creates global Temporary Table
//void readcolumns(FILE *adding, FILE *readColumn, int maxcolumns, struct primaryKey primaryKey[]);
//void addingvalues(FILE *adding, struct Table table);
int main() {
    FILE *write;
    FILE *adding;
    FILE *columns;
    FILE *tables;
    FILE *name;
    write=fopen("database.sql", "w");
    adding=fopen("database.sql", "a");
    columns=fopen("columns.csv", "a+");
	tables=fopen("tables.csv", "a+");
	name=fopen("database.txt", "w");
    struct Database database;
    struct Table table;
    char data;
    int choice, maxcolumns=0, x=0, identity=0;
    char line[100];
    char *sp;
    system ("color 0b");
    if (write==NULL || adding==NULL || columns==NULL || tables==NULL || name==NULL) {
        printf("cannot open file");
        exit (0);
    }
    getDatabaseName(name, write, database);
    do {
    printf("What type of tables would do you want to create: ");
    printf("\n1- Create table\n2- Create temporary table\n3- Create global temporary table\n0- Exit\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        createTable(tables, adding, columns, database, table, &maxcolumns, identity);
//        readcolumns(adding, readColumn, maxcolumns, primaryKey);
	break;
    case 2:
    	createTemporary(tables, adding, columns, database, table, &maxcolumns, identity);
        //addingvalues(adding, table);
    break;
    case 3:
    	createGlobal(tables, adding, columns, database, table, &maxcolumns, identity);
    break;
    }
    identity++;
}while(choice!=0);
	fclose(write);
	fclose(adding);
	fclose(columns);
	fclose(tables);
    return 0;
}

void getDatabaseName(FILE *name, FILE *write, struct Database database) {
    printf("Enter the database name that you would like to create: ");
    scanf("%s", database.databaseName);
    fprintf(name, "%s", database.databaseName);
    fprintf(write, "Create Database %s\nGo\nuse %s" , database.databaseName, database.databaseName);
}

void createTable(FILE *tables, FILE *adding, FILE *columns, struct Database database, struct Table table, int *maxcolumns, int identity) {
	int x=0;
    printf("\nEnter the table name that you would like to create: ");
    scanf("%s", database.table);
    fprintf(tables, "permanent, %s\n", database.table); //prints tables into the database table
    fprintf(adding, "\ncreate table %s (", database.table);
    printf("Enter the column that you would like to be a primary key: ");
    scanf("%s", table.primaryKey);
    fprintf(adding, "\n%s int identity(1,1) primary key,", table.primaryKey); //default int datatype that increments
    do {
    printf("\nTo quit: exit\nEnter the columns that you would like to create: "); //creates columns
    scanf("%s", table.columns);
    if (!strcmp(table.columns, "Exit") || !strcmp(table.columns, "exit")) { //if exit close
        break;
    }
    //make tables a sturcture so you could store each individual column in table[x].columns then when you want to print use a for loop
    do {
    printf("\n1- Float\t2- real\n3- decimal\t4- int\n5- bigint\t6- smallint\n7- tinyint\t");
    printf("8- date\n9- time\t\t10- datetime\n11- varchar\t12- char\n13- text\t14- nchar\n15- nvarchar\t16- ntext\n17- money\n");
    printf("Enter the datatype of the column: ");
*maxcolumns++;//figures the length the end of file data
    x++;
    scanf("%d", &table.datatypes);
    switch(table.datatypes) {
    case 1:
        strcpy(table.datatype, "float");
    break;
    case 2:
        strcpy(table.datatype, "real");
    break;
    case 3:
        strcpy(table.datatype, "decimal");
    break;
    case 4:
        strcpy(table.datatype, "int");
    break;
    case 5:
        strcpy(table.datatype, "bigint");
    break;
    case 6:
        strcpy(table.datatype, "smallint");
    break;
    case 7:
        strcpy(table.datatype, "tinyint");
    break;
    case 8:
        strcpy(table.datatype, "data");
    break;
    case 9:
        strcpy(table.datatype, "time");
    break;
    case 10:
        strcpy(table.datatype, "datetime");
    break;
    case 11:
        strcpy(table.datatype, "varchar(max)");
    break;
    case 12:
        strcpy(table.datatype, "char");
    break;
    case 13:
        strcpy(table.datatype, "text");
    break;
    case 14:
        strcpy(table.datatype, "nchar");
    break;
    case 15:
        strcpy(table.datatype, "nvarchar(max)");
    break;
    case 16:
        strcpy(table.datatype, "ntext");
    break;
    case 17:
        strcpy(table.datatype, "money");
    break;
    }
    if (table.datatypes<0 && table.datatypes>18) {
        printf("invalid datatype pick a number between 0 and 17");
        continue;
    }
    else if (table.datatypes>0 && table.datatypes<18) {
        break;
    }
    }while(1);
    printf("\n");
    do {
    printf("\nWould you like the program to allow null values\n1- Yes\t2- No\n");
    scanf("%d", &table.null);
    if (table.null==1) {
        strcpy(table.nullvalue, "");
    }
    else if (table.null==2) {
        strcpy(table.nullvalue, "not null");
    }
     fprintf(columns, "%d, %s, %s, %s\n", identity, table.columns, table.datatype, table.nullvalue); //prints data columns into file
    if(table.null<1 || table.null>2) {
        printf("\nEnter either 1 or 2");
        continue;
    }
    else if (table.null<3 && table.null>0) {
        break;
    }
    }while(1);
    fprintf(adding, "\n%s %s %s,",  table.columns, table.datatype, table.nullvalue);
}while(1);
fprintf(adding, ");");
}


void createTemporary(FILE *tables, FILE *adding, FILE *columns, struct Database database, struct Table table, int *maxcolumns, int identity) {
	int x=0;
    printf("\nEnter the table name that you would like to create: ");
    scanf("%s", database.table);
    fprintf(tables, "temporary, %s\n", database.table); //prints tables into the database table
    fprintf(adding, "\ncreate table #%s (", database.table);
    printf("\nTo quit: exit\nEnter the column that you would like to be a primary key: ");
    scanf("%s", table.primaryKey);
    fprintf(adding, "\n%s int identity(1,1) primary key,", table.primaryKey); //default int datatype that increments
    do {
    printf("Enter the columns that you would like to create: "); //creates columns
    scanf("%s", table.columns);
    if (!strcmp(table.columns, "Exit") || !strcmp(table.columns, "exit")) { //if exit close
        break;
    }
    //make tables a sturcture so you could store each individual column in table[x].columns then when you want to print use a for loop
    do {
    printf("\n1- Float\t2- real\n3- decimal\t4- int\n5- bigint\t6- smallint\n7- tinyint\t");
    printf("8- date\n9- time\t\t10- datetime\n11- varchar\t12- char\n13- text\t14- nchar\n15- nvarchar\t16- ntext\n17- money\n");
    printf("Enter the datatype of the column: ");
*maxcolumns++;//figures the length the end of file data
    x++;
    scanf("%d", &table.datatypes);
    switch(table.datatypes) {
    case 1:
        strcpy(table.datatype, "float");
    break;
    case 2:
        strcpy(table.datatype, "real");
    break;
    case 3:
        strcpy(table.datatype, "decimal");
    break;
    case 4:
        strcpy(table.datatype, "int");
    break;
    case 5:
        strcpy(table.datatype, "bigint");
    break;
    case 6:
        strcpy(table.datatype, "smallint");
    break;
    case 7:
        strcpy(table.datatype, "tinyint");
    break;
    case 8:
        strcpy(table.datatype, "data");
    break;
    case 9:
        strcpy(table.datatype, "time");
    break;
    case 10:
        strcpy(table.datatype, "datetime");
    break;
    case 11:
        strcpy(table.datatype, "varchar(max)");
    break;
    case 12:
        strcpy(table.datatype, "char");
    break;
    case 13:
        strcpy(table.datatype, "text");
    break;
    case 14:
        strcpy(table.datatype, "nchar");
    break;
    case 15:
        strcpy(table.datatype, "nvarchar(max)");
    break;
    case 16:
        strcpy(table.datatype, "ntext");
    break;
    case 17:
        strcpy(table.datatype, "money");
    break;
    }
    if (table.datatypes<0 && table.datatypes>18) {
        printf("invalid datatype pick a number between 0 and 17");
        continue;
    }
    else if (table.datatypes>0 && table.datatypes<18) {
        break;
    }
    }while(1);
    printf("\n");
    do {
    printf("\nWould you like the program to allow null values\n1- Yes\t2- No\n");
    scanf("%d", &table.null);
    if (table.null==1) {
        strcpy(table.nullvalue, "");
    }
    else if (table.null==2) {
        strcpy(table.nullvalue, "not null");
    }
     fprintf(columns, "%d, %s, %s, %s\n", identity, table.columns, table.datatype, table.nullvalue); //prints data columns into file
    if(table.null<1 || table.null>2) {
        printf("\nEnter either 1 or 2");
        continue;
    }
    else if (table.null<3 && table.null>0) {
        break;
    }
    }while(1);
    fprintf(adding, "\n%s %s %s,",  table.columns, table.datatype, table.nullvalue);
}while(1);
fprintf(adding, ");");
}

void createGlobal(FILE *tables, FILE *adding, FILE *columns, struct Database database, struct Table table, int *maxcolumns, int identity) {
	int x=0;
    printf("\nEnter the table name that you would like to create: ");
    scanf("%s", database.table);
    fprintf(tables, "global, %s\n", database.table); //prints tables into the database table
    fprintf(adding, "\ncreate table ##%s (", database.table);
    printf("\nTo quit: exit\nEnter the column that you would like to be a primary key: ");
    scanf("%s", table.primaryKey);
    fprintf(adding, "\n%s int identity(1,1) primary key,", table.primaryKey); //default int datatype that increments
    do {
    printf("\nTo quit: exit\nEnter the columns that you would like to create: "); //creates columns
    scanf("%s", table.columns);
    if (!strcmp(table.columns, "Exit") || !strcmp(table.columns, "exit")) { //if exit close
        break;
    }
    //make tables a sturcture so you could store each individual column in table[x].columns then when you want to print use a for loop
    do {
    printf("\n1- Float\t2- real\n3- decimal\t4- int\n5- bigint\t6- smallint\n7- tinyint\t");
    printf("8- date\n9- time\t\t10- datetime\n11- varchar\t12- char\n13- text\t14- nchar\n15- nvarchar\t16- ntext\n17- money\n");
    printf("Enter the datatype of the column: ");
*maxcolumns++;//figures the length the end of file data
    x++;
    scanf("%d", &table.datatypes);
    switch(table.datatypes) {
    case 1:
        strcpy(table.datatype, "float");
    break;
    case 2:
        strcpy(table.datatype, "real");
    break;
    case 3:
        strcpy(table.datatype, "decimal");
    break;
    case 4:
        strcpy(table.datatype, "int");
    break;
    case 5:
        strcpy(table.datatype, "bigint");
    break;
    case 6:
        strcpy(table.datatype, "smallint");
    break;
    case 7:
        strcpy(table.datatype, "tinyint");
    break;
    case 8:
        strcpy(table.datatype, "data");
    break;
    case 9:
        strcpy(table.datatype, "time");
    break;
    case 10:
        strcpy(table.datatype, "datetime");
    break;
    case 11:
        strcpy(table.datatype, "varchar(max)");
    break;
    case 12:
        strcpy(table.datatype, "char");
    break;
    case 13:
        strcpy(table.datatype, "text");
    break;
    case 14:
        strcpy(table.datatype, "nchar");
    break;
    case 15:
        strcpy(table.datatype, "nvarchar(max)");
    break;
    case 16:
        strcpy(table.datatype, "ntext");
    break;
    case 17:
        strcpy(table.datatype, "money");
    break;
    }
    if (table.datatypes<0 && table.datatypes>18) {
        printf("invalid datatype pick a number between 0 and 17");
        continue;
    }
    else if (table.datatypes>0 && table.datatypes<18) {
        break;
    }
    }while(1);
    printf("\n");
    do {
    printf("\nWould you like the program to allow null values\n1- Yes\t2- No\n");
    scanf("%d", &table.null);
    if (table.null==1) {
        strcpy(table.nullvalue, "");
    }
    else if (table.null==2) {
        strcpy(table.nullvalue, "not null");
    }
     fprintf(columns, "%d, %s, %s, %s\n", identity, table.columns, table.datatype, table.nullvalue); //prints data columns into file
    if(table.null<1 || table.null>2) {
        printf("\nEnter either 1 or 2");
        continue;
    }
    else if (table.null<3 && table.null>0) {
        break;
    }
    }while(1);
    fprintf(adding, "\n%s %s %s,",  table.columns, table.datatype, table.nullvalue);
}while(1);
fprintf(adding, ");");
}
