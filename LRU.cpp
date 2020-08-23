/*
LRU cache replacement algorithm
Implemented by:
Anuj Rai (2019AIM1003)
Mahip Soni (2019AIM1006)
for CS-604(Advanced Operating System) Group Project Work
*/
#include<bits/stdc++.h>
using namespace std;

unsigned int MissCount=0,HitCount=0;

/*
Function to implement LRU page referencing algorithm
*/
void LRUReferencePage(vector<unsigned int>& LRU_queue,unsigned int cacheSize, long pageNum)
{
    unsigned int trav, l=LRU_queue.size(),pos;
    int flag=0;
    for (pos=0;pos<l;pos++)
	{
		if (LRU_queue[pos]== pageNum)
		{
		    flag=1;
			break;
		}
	}

	if (!flag)
	{
		if(l==cacheSize)
        {
            LRU_queue.pop_back();
        }
        LRU_queue.insert(LRU_queue.begin(),pageNum);
		MissCount++;
	}
	else
	{
		unsigned int temp=LRU_queue[pos];
		LRU_queue.erase(LRU_queue.begin()+pos);
		LRU_queue.insert(LRU_queue.begin(),temp);
		HitCount++;
	}
}

int main()
{   //input and output file names
    char ipFileName[8][100]={"P12.lis",}, opFileName[100]="DemoLRU.txt";
    int x,y;
    unsigned int cacheSize;
    //scanf("%s %s",ipFileName,opFileName);
     //cache size input from the user
    //cin>>cacheSize;
    for(x=0;x<8;x++)
    {
    for(y=32;y<=4096;y*=2)
    {   printf("%s %d\n",ipFileName[x],y);
        cacheSize=y;
        MissCount=0,HitCount=0;
    //time variables, to calculate runtime
    time_t start,stop;

    FILE *fp=fopen(ipFileName[x], "r");
    if(!fp)
    {
    printf("Error while opening the file: %s\n", ipFileName);
    exit(EXIT_FAILURE);
    }
    unsigned int iStartingBlock = 0, iNumberOfBlocks = 0, iIgnore = 0, iRequestNumber = 0;
    unsigned int i=0;
    vector<unsigned int> LRU_queue(cacheSize); //LRU queue
    time(&start);
    //Reading traces from file
	while (fscanf(fp, "%u %u %u %u", &iStartingBlock, &iNumberOfBlocks, &iIgnore, &iRequestNumber)!=-1)
	{
			for (i = iStartingBlock; i < (iStartingBlock + iNumberOfBlocks); i++)
			{
				LRUReferencePage(LRU_queue, cacheSize,i);

			}
	}

	time(&stop);
	fclose(fp);
	fp=fopen(opFileName,"a");
	fprintf(fp,"%s %d\n",ipFileName[x],y);
	fprintf(fp,"%u %u\n",MissCount,HitCount);
	//fprintf(fp,"iMissCount + iHitCount = %u\n", iMissCount + iHitCount);
	//fprintf(fp,"Total Requests = %u\n", iTotalRequests);
	fprintf(fp,"Hit Ratio = %5.4f %%\n", ((float)(HitCount * 100) / (HitCount + MissCount)));
	fprintf(fp,"Rounded Hit Ratio = %5.2f %%\n", floor(((float)(HitCount * 100) / (HitCount + MissCount)) * 100 + 0.5) / 100);
	fprintf(fp,"Finished in about %.0f seconds. \n", difftime(stop, start));
	fclose(fp);
    }
    }
    return 0;
}
