# family_tree_application
/*
mini Project
Name:   Sumant Wadekar
        Gaurav Gavhane

*/
#include<stdlib.h>
#include<stdio.h>
typedef struct Node
{
    struct Node* prev;
    void* data;
    int noc;
    struct Node** arr;      //pointer to array of pointers
}node;

//fn to create node

node* createnode(void* data,int noc)        //noc is no of children.
{
    node* pNew=(node*)malloc(sizeof(node));
    pNew->data=data;
    pNew->prev=NULL;
    pNew->noc=noc;
    pNew->arr=NULL;
    return pNew;
}

typedef struct queue
{
	 node* Qdata;
	struct queue* next;
}QUE;

void createqueue(QUE** fr,QUE** re)
{
	*fr=NULL;       //fr front
	*re=NULL;       //re rear
}
void enqueue(QUE** fr,QUE** re,node* root)
{
	QUE* tmp;
	tmp=(QUE*)malloc(sizeof(QUE));
	tmp->next=NULL;
	tmp->Qdata=root;
	if(*fr==NULL)
	{
		*fr=tmp;
		*re=tmp;
	}
	else
	{
		(*re)->next=tmp;
		*re=tmp;
	}
}
node* dequeue(QUE** fr,QUE** re)
{
	QUE* pdlt;
	node* dataout;
	pdlt=*fr;
	dataout=pdlt->Qdata;
	if(*fr==*re)
	{
		*fr=*re=NULL;
	}
	else
	{
		*fr=(*fr)->next;
	}
	free(pdlt);
	return dataout;
}
node* queuefront(QUE** fr)
{
	node* dataout;
	dataout=(*fr)->Qdata;
	return dataout;
}
int emptyqueue(QUE** fr)
{
	if(*fr==NULL)
		return 1;
	else
		return 0;
}

//fn to destoy Que

void destroyQ(QUE** fr,QUE** re)
{
	*fr=NULL;
	*re=NULL;
}

//fn to find ancestors upto 2 genrations
void ancenstors(node** ptrrcv)
{
node *ptr=*ptrrcv;
	if((ptr->prev)!=NULL&&((ptr->prev)->prev)==NULL)
	{
		printf("\n\t%c %s",254,(char *)((ptr->prev)->data));
		printf("\n\t%c second ancenstor for %s is absent...",254,(char *)ptr->data);
	}

	else if(ptr->prev==NULL)
		printf("\n\t%c The Ancestors for %s are absent...\n",254,(char *)ptr->data);
	else
	printf("\n\t%c %s\n\t%c %s\n",254,((ptr->prev)->data),254,(char *)((ptr->prev)->prev)->data);
}

//fn to print decendents upto 2 gernrations
void decendents(node** root)
{
	node* ptr;
	int i,cnt;
	QUE *fr,*re;
	createqueue(&fr,&re);
	ptr=*root;
	cnt=0;
	if(ptr->noc==0)
		{
			printf("\n\t%c No Any Decendant for %s\n",254,(char *)ptr->data);
		}
	else
	{
	while(ptr)
	{

			for(i=0;i<ptr->noc;i++)
			{
				printf("\n\t%c %s",254,(char *)(ptr->arr[i])->data);
				if(cnt==0)
				enqueue(&fr,&re,ptr->arr[i]);
			}
			cnt=1;


		if(!emptyqueue(&fr))
		{
			ptr=dequeue(&fr,&re);
		}
		else
		{
			 ptr=NULL;
		}

	}
	}
	destroyQ(&fr,&re);
}



/*
mini Project 
Name:   Sumant Wadekar
        Gaurav Gavhane

*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include"miniproj.h"
#include<ctype.h>

void* getdata(int* noc)
{
    void* data;
    int i;char ch;
    char* nm=(char*)malloc(20*sizeof(char));
    printf("\nEnter Name:\t");
    scanf("%s",nm);
    for(i=0;nm[i]!='\0';i++)
    {
        nm[i]=toupper(nm[i]);              //inputted name is converted to upper case.
    }
    data=nm;
    while(1)
    {
        printf("\nEnter No. of children for %s:\t",(char*)data);
        if(scanf("%d",noc)!=1)
        {
            printf("\n\tPlease Enter valid children no.(0 or above 0)\n");
            while((ch=getchar())!='\n' && ch!=EOF);   //preventing user from inputing no of children as string.
            continue;
        }
        if(*noc>=0)
            break;
    }

    return data;
}

//fn to create tree

node* insert(node *rootprev)
{
    node* root;
    int i;
    void* d;
    int noc;
    d=getdata(&noc);
    root=createnode(d,noc);
        if(noc==0)
        {
                root->prev=rootprev;
                root->arr=NULL;
                return root;
        }
        node**temparr=(node**)malloc(noc*sizeof(node*));
        root->prev=rootprev;
        for( i=0;i<noc;i++)
        {
            printf("\nChild %d of %s",i+1,(char*)root->data);
            temparr[i]=insert(root);
        }
            root->arr=temparr;
        return root;
}

FILE *fp;   //file ptr from which input data taken
// fn to create tree using data from file
node* inputFromFile(node *rootprev)
{
    node* root;
    int i,noc;
    void* d;
    char* name;
    name=(char *)malloc(sizeof(char)*15);

    while((fscanf(fp,"%s %d",name,&noc)!=EOF))
    {
        for(i=0;name[i]!='\0';i++)
            name[i]=toupper(name[i]);   //converts name into uppercase
        root=createnode(name,noc);
        if(noc==0)
        {
                root->prev=rootprev;
                root->arr=NULL;
                return root;
        }
        node** a=(node**)malloc(noc*sizeof(node*));
        root->prev=rootprev;
        for( i=0;i<noc;i++)
        {
          a[i]=inputFromFile(root);
        }
        root->arr=a;
        return root;
    }
}
// fn to print tabs which is useful in making indendated type display of tree.
void printTab()
{
    printf("\t");
}
// fn to display tree in indented format.
void display(node* root,int *n)
{   int i,j;
    node** temp;
    if(root==NULL)
    {
        printf("\n\tFamily Tree is Empty ....please Firstly Create it\n");
        return;
    }
    printf("%c %s\n",254,(char*)(root->data));
    temp=root->arr;
    if(root->noc>0)
        *n=*n+1;
    for( i=0;i<root->noc;i++)
    {

        for( j=0;j<(*n);j++)
            printTab();
        node* a=temp[i];
        display(a,n);

    }
    if(root->noc>0)
    *n-=1;
}
// fn to search name in family tree.

node* search(node** root,char* snm)
{
	node* ptr;
	int i,cnt;
	node* tempptr;
	QUE *fr,*re;
	createqueue(&fr,&re);
	ptr=*root;
	while(ptr!=NULL)
	{
		if(strcmp(ptr->data,snm)==0)
		{
			return ptr;
		}
		cnt=ptr->noc;
		for(i=0;i<cnt;i++)
		{
			if(ptr->arr[i]!=NULL)
			enqueue(&fr,&re,ptr->arr[i]);
		}
		if(!emptyqueue(&fr))
		{
			ptr=dequeue(&fr,&re);
		}
		else
		{

		       ptr=NULL;
		}
	}
	destroyQ(&fr,&re);
	return ptr;

}
// fn to export manually inputed family tree data into new file.

node* exportToFile(node *root,FILE *fexport)
{
    node* ptr;
    int i,cnt;
	QUE *fr,*re;
	createqueue(&fr,&re);
	ptr=root;
	while(ptr!=NULL)
	{
		fprintf(fexport,"%s %d\n",(char*)(ptr->data),(ptr->noc));
		cnt=ptr->noc;
		for(i=0;i<cnt;i++)
		{
			if(ptr->arr[i]!=NULL)
			enqueue(&fr,&re,ptr->arr[i]);
		}
		if(!emptyqueue(&fr))
		{
			ptr=dequeue(&fr,&re);
		}
		else
		{

		       ptr=NULL;
		}
	}
	destroyQ(&fr,&re);
	return ptr;


}


int main()
{
    node* root=NULL,*rootprev=NULL,*ptr=NULL;
    char snm[15];
    int n=0,opt,i,fopt;
    char ch;
    FILE *fexport;
    printf("\n\t\t\t\t\t\t\t\t\t\t...%c%c%c  Family Tree Application  %c%c%c...\n\n",254,254,254,254,254,254);
    while(1)
    {
        printf("\nMenu:\n\n1. Create Tree\n2. Display\n3. Search\n4. Export To File\n5. Destroy Family Tree\n6. Exit\nYour Option:\t");
       if(scanf("%d",&opt)!=1)
            while(ch=getchar()!='\n'&&ch!=EOF);
        if(opt==6)
        {
            printf("\nAre You sure to Exit(y/n):");
            scanf("%s",&ch);
            if(ch=='y'||ch=='Y')
                break;
            else
                continue;
        }
        switch(opt)
        {
            case 1:
                printf("\nWant to use File for Input(y/n):\t");
                scanf("%s",&ch);
                if((ch=='y')||(ch=='Y'))
                {
                    printf("\nChoose File:\n\n1.kaurav_pandav Family\n\n2.Bajirao Family\n\nYour Option:\t");
                    scanf("%d",&fopt);
                    if(fopt==1)
                        fp=fopen("kaurav_family.txt","r");
                    else
                        fp=fopen("bajirao_family.txt","r");
                    if(fp==NULL)
                    {
                        printf("\n\tEither File is Empty or File Not found.");
                        return 0;
                    }
                    printf("\n\tData successfully read from file to buid family tree...");
                    root=inputFromFile(rootprev);
                }
                else
                    root=insert(rootprev);break;
            case 2:
                display(root,&n);break;
            case 3:
                if(root==NULL)
                {
                    printf("\n\tFamily Tree is Empty.... Please Firstly Create it to search\n");
                    continue;
                }
                display(root,&n);
                printf("\n\n\tEnter Name to be searched:\t");
				scanf("%s",snm);
				for(i=0;snm[i]!='\0';i++)
                    snm[i]=toupper(snm[i]);
				ptr=search(&root,snm);
				if(ptr==NULL)
					printf("\n\t%s Not Found in family tree...",snm);
				else
				{
					printf("\n\t%s",(char*)ptr->data);
					printf("\t%d\n",ptr->noc);
					printf("\n\tAncenstors of %s:\n",(char*)ptr->data);
					ancenstors(&ptr);
					printf("\n\n\tDecendents of %s:\n",(char*)ptr->data);
					decendents(&ptr);
				}
				break;
            case 4:
                fexport=fopen("familyfile.txt","w");
                if(root==NULL)
                {
                    printf("\n\tFamily tree is empty...  Please firstly create it to export");
                    continue;
                }
                root=exportToFile(root,fexport);
                printf("\n\tData Successfuly exported to file....Please check familyfile.txt File in current folder.\n");
                fclose(fexport);break;

            case 5:
                if(root==NULL)
                {
                    printf("\n\tFamily Tree is already empty... Firstly create it to Destroy.");
                    continue;
                }
                printf("\n\tRecent Family Tree Destroyed Successfully....\n");
                root=NULL;break;

            default:
                printf("\n\tInvalid Input.... Please Enter valid Option\n");

        }
    }
    return 0;
}

/*
Kuru 1
Shantanu 3
Bhishma 0
Chitrangada 0
Vichitravirya 3
Dhritrashtra 101
Duryodhana 2
lakshman 0
lakshmana 0
Yuyutsu 0
Dussasana 0
Dusaha 0
Jalsandha 0
Sudushil 0
Bheembal 0
Subahu 0
Sahishnu 0
Yekkundi 0
Durdhar 0
Durmukh 0
Bindoo 0
Krup 0
Chitra 0
Durmad 0
Dushchar 0
Sattva 0
Chitraksha 0
Urnanabhi 0
Chitrabahoo 0
Sulochan 0
Sushabh 0
Chitravarma 0
Asasen 0
Mahabahu 0
Samdukkha 0
Mochan 0
Sumami 0
Vibasu 0
Vikar 0
Chitrasharasan 0
Pramah 0
Somvar 0
Man 0
Satyasandh 0
Vivas 0
Vikarna 0
Upchitra 0 
Chitrakuntal 0
Bheembahu 0
Sund 0
Valaki 0
Upyoddha 0
Balavardha 0
Durvighna 0
Bheemkarmi 0
Upanand 0
Anasindhu 0
Somkirti 0
Kudpad 0
Ashtabahu 0
Ghor 0
Roudrakarma 0
Veerbahoo 0
Kananaa 0
Kudasi 0
Deerghbahu 0
Adityaketoo 0
Pratham 0
Prayaami 0
Veeryanad 0
Deerghtaal 0
Vikatbahoo 0
Drudhrath 0
Durmashan 0
Ugrashrava 0
Ugra 0
Amay 0
Kudbheree 0
Bheemrathee 0
Avataap 0
Nandak 0
Upanandak 0
Chalsandhi 0
Broohak 0
Suvaat 0
Nagdit 0
Vind 0
Anuvind 0
Arajeev 0
Budhkshetra 0
Droodhhasta 0
Ugraheet 0
Kavachee 0
Kathkoond 0
Aniket 0
Kundi 0
Durodhar 0
Shathasta 0
Shubhkarma 0
Saprapta 0
Dupranit 0
Bahudhami 0
Yuyutsoo 0
Dhanurdhar 0
Senanee 0
Veer 0
Pramathee 0
Droodhsandhee 0
Dushla(Daughter) 0
vidur 0 
Pandu 5
Yudhishthira 1
Prativindhya 0
Bhim 2
Ghatotkach 0
Sutsom 0
Arjun 2
Abhimanyu 1
Parikshit 1
Janamejaya 0
Sutkarma 0
Nakul 1
Shatangada 0
Sahdeva 1
Shutsena 0
 */

