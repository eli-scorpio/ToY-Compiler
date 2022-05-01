
#include"StructureRecord.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define STOP 0

struct strucureList * init_strucure_list( struct strucureList *thisStructureList)
{
   

    thisStructureList = (struct strucureList*)malloc(sizeof( struct strucureList));
  // int i;
    for( int i = 0 ;i<MAX_SIZE;i++)
    {
     //   thisStructureList->arrayStucure[i].structureName ="NULL";
        strcpy(thisStructureList->arrayStucure[i].structureName,"NULL");

        //initlaiza of filed
        for( int j = 0 ;j<1024;j++)
        {
            //thisStructureList->arrayStucure[i].filedList[j].identificationName ="NULL";
            strcpy( thisStructureList->arrayStucure[i].filedList[j].identificationName,"NULL");

//            thisStructureList->arrayStucure[i].filedList[j].declarationType ="VOID";
            strcpy(thisStructureList->arrayStucure[i].filedList[j].declarationType,"NULL");
        }
    }

   return thisStructureList;
}

void add_strucure_name( struct strucureList *thisStructureList,char *structureName)
{
    struct strucureList *tempStucureList = thisStructureList;
    int stopSignal = STOP;

    for(int i = 0 ;(i < MAX_SIZE)&&(!stopSignal);i++)
    {
        //char *temp = tempStucureList->arrayStucure[i].structureName;
       //char *empatyString = "NULL";
        if(strcmp(thisStructureList->arrayStucure[i].structureName,"NULL")==0)
        {
           // thisStructureList->arrayStucure[i].structureName = structureName;
            strcpy(thisStructureList->arrayStucure[i].structureName,structureName);
            stopSignal =1;
            return ;

        }
    }
}
void add_structureFiled( struct strucureList *thisStructureList,char * structureName,char *filedType,char * filedName)
{
    struct strucureList *tempStucureList = thisStructureList;
    int stopSignal = STOP;


   // char *empatyString = "NULL";
    for(int i = 0 ;(i < MAX_SIZE)&&(!stopSignal);i++)
    {
      //  char *tempStrctureName = tempStucureList->arrayStucure[i].structureName;
        /*
         * Finding the strucure Name
         */
        if(strcmp(thisStructureList->arrayStucure[i].structureName,structureName)==0)
        {

           // iterate the filed list
          //char *empatyString = "NULL";
           for(int j = 0 ;j<1024;j++)
            {
              // char *tempSring = tempStucureList->arrayStucure[i].filedList[j].identificationName;
               if(strcmp(tempStucureList->arrayStucure[i].filedList[j].identificationName,"NULL")==0)
               {

//                  thisStructureList->arrayStucure[i].filedList[j].identificationName = filedName;

                  strcpy(thisStructureList->arrayStucure[i].filedList[j].identificationName,filedName);

                 // thisStructureList->arrayStucure[i].filedList[j].declarationType=filedType;
                  strcpy(thisStructureList->arrayStucure[i].filedList[j].declarationType,filedType);
                  // Return directly;
                  return;
               }

            }


        }
    }


}
/*
 * Return 1 true
 * Return 0 false
 */
int structureNameExistChecker( struct strucureList *thisStructureList,char *  structureName)
{
    int stopSignal = STOP;

    for(int i = 0 ;(i < MAX_SIZE)&&(!stopSignal);i++)
    {




       // char *temp = thisStructureList->arrayStucure[i].structureName;
       // char *compardString = structureName;
        if(strcmp(thisStructureList->arrayStucure[i].structureName,structureName)==0)
        {
            // Find and direcly return 
            stopSignal =1;
            return 1;

        }
    }
    return 0;
}
/*
 * Return 1 true
 * Return 0 false
 */

int checker_structureFiled( struct strucureList *thisStructureList,char * stuName,char * fieldName)
{

  //  struct strucureList *tempStucureList = thisStructureList;
    //int stopSignal = STOP;

    for(int i = 0 ;i < MAX_SIZE;i++)
    {
        //har *tempStrctureName = tempStucureList->arrayStucure[i].structureName;
        /*
         * Finding the strucure Name
         */
        if(strcmp(thisStructureList->arrayStucure[i].structureName,stuName)==0)
        {

           // iterate the filed list
           //char *ComparedFiled  = fieldName;
           for(int j = 0 ;j<1024;j++)
            {
               //char *tempSring =tempStucureList->arrayStucure[i].filedList[j].identificationName;
               if(strcmp(thisStructureList->arrayStucure[i].filedList[j].identificationName,fieldName)==0)
               {

                 //thisStructureList->arrayStucure[i].filedList[j] = filedName;
                  // Return directly;
                  return 1;
               }

            }


        }
      
    }



// for case no filed
    return 0;

}


char *returnFiledTypeForSpecificStrucure( struct strucureList *thisStructureList,char * stuName,char * fieldName)
{
    //  struct strucureList *tempStucureList = thisStructureList;
    //int stopSignal = STOP;
    char filetYPE[1024];
  
    for(int i = 0 ;i < MAX_SIZE;i++)
    {
        //har *tempStrctureName = tempStucureList->arrayStucure[i].structureName;
        /*
         * Finding the strucure Name
         */
        if(strcmp(thisStructureList->arrayStucure[i].structureName,stuName)==0)
        {

            // iterate the filed list
            //char *ComparedFiled  = fieldName;
           
            for(int j = 0 ;j<1024;j++)
            {
                //char *tempSring =tempStucureList->arrayStucure[i].filedList[j].identificationName;
                if(strcmp(thisStructureList->arrayStucure[i].filedList[j].identificationName,fieldName)==0)
                {
                    char *tempValue = thisStructureList->arrayStucure[i].filedList[j].identificationName;
                   // printf("This temp vaulue in the second loop is %s\n",tempValue);

                    //thisStructureList->arrayStucure[i].filedList[j] = filedName;
                    // Return directly;
                     char *reruntType = thisStructureList->arrayStucure[i].filedList[j].declarationType;
                    // printf("Prinitng return value is %s\n",reruntType);
                     return reruntType;

                }

            }


        }

    }



// for case no filed
    return NULL;
}


void print_strucureInfo(struct strucureList *thisStructureList,char *structureName)
{
    printf("@@@@This is the summary information for Strcture %s information\n",structureName);
    printf("_______________________________________________\n");
    int i;
    for(i = 0 ;i< MAX_SIZE;i++)
    {
        char *tempStructureName=thisStructureList->arrayStucure[i].structureName;
        if(strcmp(tempStructureName,structureName)==0)
        {
            int j;
                printf("_______________________________________________\n");
            printf("These are the information for filed info \n");
            for(j = 0;j<5;j++)
            {
                  printf("_______________________________________________\n");
                char *filedName = thisStructureList->arrayStucure[i].filedList[j].identificationName;
                char *filedType = thisStructureList->arrayStucure[i].filedList[j].declarationType;

                printf("The Type of this variable is %s",filedType);

                printf("The ID of this variale is %s\n",filedName);

                printf("_______________________________________________\n");
            }

        }
    }

}
