/*
mini Project Pair no.16
Name:   Sumant Wadekar(2016BTECS00022)
        Gaurav Gavhane(2016BTECS00071)

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
