/* Code */
int euclid(int m, int n)
{
int r, **t;
/*while(i==d)
*/if (n>m) // ">"
{
r=m; // "="
m=n; // "="
n=r; // "="
}
printf("/**/if\"while");
r = m % n; // "=", "%"
while (r != 0) // "!="
{
m=n; // "="
n=r; // "="
r=m % n; // "=", "%"
}
return n;
}