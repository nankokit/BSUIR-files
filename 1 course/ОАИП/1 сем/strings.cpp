# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

int len(char *str)
{
    int i=0,n;
    while (str[i]!='\0')
    {
        i++;
    }
    
    n=i;
    return n;
    
}
int output (char *str)
{
    printf("\n");
    int n=len(str), i;
    for (i=0; i<n ; i++)
        printf ("%c", str[i]);
    
    printf("\n");
    return 0;
}
//  asd   fgh //
// asd    
//asd fgh//


char *del_space(char *str)
{
    int i, n=len(str);
    
    for (i=0; i< n-1; i++)
    {
        if (str[i]== ' ')
        {
            if (i==0)
            {
                for(int j=i; j<n-1; j++)
                    str[j]=str[j+1];
                
                str=(char*)realloc(str, sizeof(char) * n);
                n--;
                i--;
            }
            
            if (str[i+1]== ' ')
            {
                 for(int j=i+1; j<n-1; j++)
                    str[j]=str[j+1];
                
                str=(char*)realloc(str, sizeof(char) * n);
                n--;
                i--;
            }
            //.....az__'\0'
           // if (str[i+1]== '\0')
           // {
            //    str=(char*)realloc(str, sizeof(char) * n);
             //   n--;
            //    i--;
            //}
        }
    }
    
    
    
    
    return str;
}


int upper(char *s)
{
    int i, n=len(s), cnt=0;
    
    for (i=0; i< n; i++)
        if (s[i] >='A' && s[i] <= 'Z')
            cnt++;
    
    return cnt;
}


char* upper_to_lower(char *s)
{
    int i, n=len(s);
    
    for (i=0; i< n; i++)
        if (s[i] >='A' && s[i] <= 'Z')
            s[i]=s[i] - ('A'-'a');
    
    return s;
}

char* lower_to_upper_letter(char *s, int i)
{
    s[i]=s[i] + ('A'-'a');
    
    return s;
}

int if_letter(char s)
{
    if ((s>='a' && s <='z') || (s>='A' && s<='Z') ) return 1;
    else return 0;
    
}

char *upper_after_dot(char *str)
{
    int i, n=len(str);
    
    for (i=0; i< n-2; i++)
    {
        //if (i==0 && (str[i]>='a' && str[i] <='z') ) str=lower_to_upper_letter(str,i);
        //if (str[i]=='.' && (str[i+2]>='a' && str[i+2] <='z'))  str=lower_to_upper_letter(str,i+2);
        if (i==0)
        {
            while (if_letter(str[i])==0)
            {
                i++;
            }
            if ((str[i]>='a' && str[i] <='z') ) str=lower_to_upper_letter(str,i);
        }
        if (str[i]=='.')
        {
            while (if_letter(str[i])==0)
            {
                i++;
            }
            if (str[i]>='a' && str[i] <='z') str=lower_to_upper_letter(str,i);
             
        }
        
    }
    // ._a
    // i i+1 i+2
    return str;
}













int main()
{
char * str;
str= (char*)calloc(1,1);
	
fgets (str,255,stdin);
int i=0;

//output(str);
//str=del_space(str);

output(upper_after_dot(str));

//printf ("\n %d", k);
//char s='Z';
//printf ("%d", s );

}