/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#include "code_scan.h"
#include "utils.h"
long long util_file_size(const char*path){struct stat st;if(stat(path,&st)!=0)return -1;return st.st_size;}
char*util_read_file(const char*path,long long*size){FILE*f=fopen(path,"rb");if(!f)return NULL;fseek(f,0,SEEK_END);long long sz=ftell(f);if(sz<0){fclose(f);return NULL;}rewind(f);char*buf=malloc((size_t)sz+1);if(!buf){fclose(f);return NULL;}size_t r=fread(buf,1,(size_t)sz,f);fclose(f);buf[r]=0;if(size)*size=r;return buf;}
int util_write_file(const char*path,const char*data,long long len){FILE*f=fopen(path,"wb");if(!f)return 0;size_t w=fwrite(data,1,(size_t)len,f);fclose(f);return w==(size_t)len;}
int util_is_dir(const char*path){struct stat st;if(stat(path,&st)!=0)return 0;return S_ISDIR(st.st_mode);}
int util_is_file(const char*path){struct stat st;if(stat(path,&st)!=0)return 0;return S_ISREG(st.st_mode);}
int util_is_symlink(const char*path){struct stat st;if(lstat(path,&st)!=0)return 0;return S_ISLNK(st.st_mode);}
int util_mkdir_p(const char*path){char tmp[CODE_SCAN_MAX_PATH];char*p=NULL;size_t len;code_scan_snprintf(tmp,sizeof(tmp),"%s",path);len=strlen(tmp);if(tmp[len-1]=='/')tmp[len-1]=0;for(p=tmp+1;*p;p++){if(*p=='/'){*p=0;mkdir(tmp,0755);*p='/';}}return mkdir(tmp,0755);}
int util_file_exists(const char*path){return access(path,F_OK)==0;}
char*util_realpath(const char*path){char*buf=malloc(CODE_SCAN_MAX_PATH);if(!buf)return NULL;char*r=realpath(path,buf);if(!r){free(buf);return NULL;}return buf;}
char*util_dirname(const char*path){char*buf=code_scan_strdup(path);if(!buf)return NULL;char*p=strrchr(buf,'/');if(p)*p=0;else code_scan_snprintf(buf,4,".");return buf;}
char*util_basename(const char*path){const char*p=strrchr(path,'/');return p?code_scan_strdup(p+1):code_scan_strdup(path);}
char*util_extension(const char*path){const char*dot=strrchr(path,'.');if(!dot||strchr(dot,'/'))return NULL;return code_scan_strdup(dot+1);}
char*util_join_path(const char*dir,const char*file){size_t dl=strlen(dir);size_t fl=strlen(file);char*buf=malloc(dl+fl+2);if(!buf)return NULL;memcpy(buf,dir,dl);if(dl>0&&dir[dl-1]!='/')buf[dl++]='/';memcpy(buf+dl,file,fl+1);return buf;}
int util_str_eq(const char*a,const char*b){if(!a&&!b)return 1;if(!a||!b)return 0;while(*a&&*b&&*a==*b){a++;b++;}return *a==*b;}
int util_str_case_eq(const char*a,const char*b){if(!a&&!b)return 1;if(!a||!b)return 0;while(*a&&*b){char ca=*a;char cb=*b;if(ca>='A'&&ca<='Z')ca+='a'-'A';if(cb>='A'&&cb<='Z')cb+='a'-'A';if(ca!=cb)return 0;a++;b++;}return *a==*b;}
int util_is_source(const char*path){const char*ext=util_extension(path);if(!ext)return 0;int r=util_str_case_eq(ext,"c")||util_str_case_eq(ext,"cc")||util_str_case_eq(ext,"cpp")||util_str_case_eq(ext,"cxx");free((void*)ext);return r;}
int util_is_header(const char*path){const char*ext=util_extension(path);if(!ext)return 0;int r=util_str_case_eq(ext,"h")||util_str_case_eq(ext,"hh")||util_str_case_eq(ext,"hpp")||util_str_case_eq(ext,"hxx");free((void*)ext);return r;}
int util_is_c_file(const char*path){const char*ext=util_extension(path);if(!ext)return 0;int r=util_str_case_eq(ext,"c");free((void*)ext);return r;}
int util_is_cpp_file(const char*path){const char*ext=util_extension(path);if(!ext)return 0;int r=util_str_case_eq(ext,"cpp")||util_str_case_eq(ext,"cc")||util_str_case_eq(ext,"cxx");free((void*)ext);return r;}
int util_binary_file(const char*path){long long sz;char*data=util_read_file(path,&sz);if(!data)return 0;int binary=0;for(long long i=0;i<sz&&i<1024;i++){unsigned char c=data[i];if(c==0){binary=1;break;}}free(data);return binary;}
int util_count_lines(const char*content,long long size){int lines=0;for(long long i=0;i<size;i++){if(content[i]=='\n')lines++;}if(size>0&&content[size-1]!='\n')lines++;return lines;}
char*util_get_line(const char*content,int line){if(line<1)return NULL;int cur=1;const char*start=content;const char*p=content;while(*p){if(cur==line&&(*p!='\n')){start=p;while(*p&&*p!='\n')p++;size_t len=(size_t)(p-start);char*buf=malloc(len+1);memcpy(buf,start,len);buf[len]=0;return buf;}if(*p=='\n')cur++;p++;}return NULL;}
int util_get_line_number(const char*content,const char*pos){if(!content||!pos||pos<content)return 0;int line=1;const char*p=content;while(p<pos){if(*p=='\n')line++;p++;}return line;}
int util_get_column(const char*content,const char*pos){if(!content||!pos||pos<content)return 0;int col=1;const char*p=pos-1;while(p>=content&&*p!='\n'){col++;p--;}return col;}
char*util_strip_ext(const char*path){char*buf=code_scan_strdup(path);if(!buf)return NULL;char*dot=strrchr(buf,'.');if(dot&&!strchr(dot,'/'))*dot=0;return buf;}
char*util_replace_ext(const char*path,const char*ext){char*buf=util_strip_ext(path);if(!buf)return NULL;char*res=util_concat(buf,ext);free(buf);return res;}
char*util_concat(const char*a,const char*b){if(!a||!b)return NULL;size_t al=strlen(a),bl=strlen(b);char*r=malloc(al+bl+1);memcpy(r,a,al);memcpy(r+al,b,bl+1);return r;}
int util_glob_match(const char*pattern,const char*str){const char*p=pattern;const char*s=str;while(*p&&*s){if(*p=='*'){p++;if(!*p)return 1;while(*s){if(util_glob_match(p,s))return 1;s++;}return 0;}else if(*p=='?'){p++;s++;}else{if(*p!=*s)return 0;p++;s++;}}while(*p=='*')p++;return *p==0&&*s==0;}
int util_starts_with(const char*s,const char*pre){if(!s||!pre)return 0;while(*pre){if(*s!=*pre)return 0;s++;pre++;}return 1;}
int util_ends_with(const char*s,const char*suf){if(!s||!suf)return 0;size_t sl=strlen(s);size_t sul=strlen(suf);if(sul>sl)return 0;return util_str_eq(s+sl-sul,suf);}
char*util_trim(char*s){if(!s)return NULL;while(*s&&(*s==' '||*s=='\t'||*s=='\n'||*s=='\r'))s++;if(!*s)return s;char*end=s+strlen(s)-1;while(end>s&&(*end==' '||*end=='\t'||*end=='\n'||*end=='\r'))end--;*(end+1)=0;return s;}
char*util_strdup(const char*s){if(!s)return NULL;size_t l=strlen(s);char*b=malloc(l+1);if(!b)return NULL;memcpy(b,s,l+1);return b;}
char*util_strndup(const char*s,size_t n){if(!s)return NULL;size_t l=strnlen(s,n);char*b=malloc(l+1);if(!b)return NULL;memcpy(b,s,l);b[l]=0;return b;}
char*util_join(const char**strs,int n,const char*sep){if(!strs||n<1)return NULL;size_t total=0;for(int i=0;i<n;i++)if(strs[i])total+=strlen(strs[i]);size_t sl=sep?strlen(sep):0;total+=sl*(n-1);char*r=malloc(total+1);r[0]=0;for(int i=0;i<n;i++){if(i>0&&sep)strcat(r,sep);if(strs[i])strcat(r,strs[i]);}return r;}
char**util_split(const char*s,char sep,int*n){if(!s){*n=0;return NULL;}int count=1;for(const char*p=s;*p;p++)if(*p==sep)count++;char**r=calloc((size_t)count,sizeof(char*));if(!r){*n=0;return NULL;}int idx=0;const char*start=s;for(const char*p=s;;p++){if(*p==sep||*p==0){size_t len=(size_t)(p-start);r[idx]=util_strndup(start,len);idx++;if(*p==0)break;start=p+1;}}*n=idx;return r;}
int util_is_whitespace(char c){return c==' '||c=='\t'||c=='\n'||c=='\r'||c=='\v'||c=='\f';}
int util_is_ident_char(char c){return isalnum((unsigned char)c)||c=='_';}
int util_is_digit(char c){return c>='0'&&c<='9';}
int util_is_hex_digit(char c){return util_is_digit(c)||(c>='a'&&c<='f')||(c>='A'&&c<='F');}
int util_is_octal_digit(char c){return c>='0'&&c<='7';}
void util_lower(char*s){if(!s)return;for(;*s;s++){if(*s>='A'&&*s<='Z')*s+='a'-'A';}}
void util_upper(char*s){if(!s)return;for(;*s;s++){if(*s>='a'&&*s<='z')*s-='a'-'A';}}
long long util_ato64(const char*s){if(!s)return 0;int neg=0;if(*s=='-'){neg=1;s++;}else if(*s=='+')s++;long long v=0;while(*s>='0'&&*s<='9'){v=v*10+(*s-'0');s++;}return neg?-v:v;}
unsigned long long util_atou64(const char*s){if(!s)return 0;unsigned long long v=0;while(*s>='0'&&*s<='9'){v=v*10+(*s-'0');s++;}return v;}
double util_atof(const char*s){if(!s)return 0.0;return strtod(s,NULL);}
char*util_itoa(long long v,char*buf,size_t sz){if(!buf||sz<2)return NULL;int neg=0;if(v<0){neg=1;v=-v;}char tmp[64];int i=0;do{tmp[i++]=(char)('0'+(v%10));v/=10;}while(v>0);if(neg)tmp[i++]='-';int j=0;if(neg){if((size_t)(j+1)<sz)buf[j++]='-';}for(i--;i>=0&&(size_t)j<sz-1;i--){buf[j++]=tmp[i];}buf[j]=0;return buf;}
int util_hex_to_int(char c){if(c>='0'&&c<='9')return c-'0';if(c>='a'&&c<='f')return 10+(c-'a');if(c>='A'&&c<='F')return 10+(c-'A');return -1;}
char util_int_to_hex(int v){if(v<0||v>15)return '0';return v<10?(char)('0'+v):(char)('a'+(v-10));}
unsigned long util_hash_str(const char*s){unsigned long h=5381;int c;while((c=*s++))h=((h<<5)+h)+(unsigned char)c;return h;}
unsigned long util_hash_file(const char*path){long long sz;char*data=util_read_file(path,&sz);if(!data)return 0;unsigned long h=util_hash_str(data);free(data);return h;}
int util_is_power_of_2(unsigned long long v){return v&&!(v&(v-1));}
unsigned long long util_next_power_of_2(unsigned long long v){v--;v|=v>>1;v|=v>>2;v|=v>>4;v|=v>>8;v|=v>>16;v|=v>>32;return v+1;}
int util_count_bits(unsigned long long v){int c=0;while(v){c+=v&1;v>>=1;}return c;}
void util_sleep_ms(int ms){struct timespec ts;ts.tv_sec=ms/1000;ts.tv_nsec=(long)(ms%1000)*1000000;nanosleep(&ts,NULL);}
