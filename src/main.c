/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#include "code_scan.h"
#include "lexer.h"
#include "parser.h"
#include "preprocessor.h"
#include "symbol.h"
#include "controlflow.h"
#include "dataflow.h"
#include "analysis.h"
#include "reporter.h"
#include "walker.h"
#include "database.h"
#include "config.h"
#include "utils.h"
#include "checks_mem.h"
#include "checks_sec.h"
#include "checks_syntax.h"
#include "checks_types.h"
#include "checks_perf.h"
#include "checks_concurrency.h"
#include "checks_quality.h"
#include "checks_buf.h"
#include "checks_c.h"
#include "checks_cpp.h"
#include "checks_csharp.h"
#include "checks_java.h"
#include "checks_js.h"
#include "checks_ts.h"
#include "checks_python.h"
#include "checks_ruby.h"
#include "checks_php.h"
#include "checks_go.h"
#include "checks_rust.h"
#include "checks_swift.h"
#include "checks_kotlin.h"
#include "checks_scala.h"
#include "checks_dart.h"
#include "checks_haskell.h"
#include "checks_lua.h"
#include "checks_r.h"
#include "checks_julia.h"
#include "checks_perl.h"
#include "checks_shell.h"
#include "checks_sql.h"
#include "checks_html.h"
#include "checks_css.h"
#include "checks_yaml.h"
#include "checks_objectivec.h"
#include "checks_groovy.h"
#include "checks_fortran.h"
#include "checks_cobol.h"
#include "checks_basic.h"
#include "checks_pascal.h"
#include "checks_ada.h"
#include "checks_lisp.h"
#include "checks_prolog.h"
#include "checks_erlang.h"
#include "checks_elixir.h"
#include "checks_clojure.h"
#include "checks_fsharp.h"
#include "checks_visualbasic.h"
#include "checks_powershell.h"
#include "checks_matlab.h"
#include "checks_d.h"
#include "checks_dockerfile.h"
#include "checks_json.h"
#include "checks_toml.h"
#include "checks_cmake.h"
#include "checks_makefile.h"
#include "checks_tex.h"
#include "checks_vue.h"
#include "checks_svelte.h"
#include "checks_solidity.h"
#include "checks_graphql.h"
#include "checks_tcl.h"
#include "checks_coffeescript.h"
#include "checks_nim.h"
#include "checks_zig.h"
#include "checks_ocaml.h"
#include "checks_purescript.h"
#include "checks_racket.h"
#include "checks_scheme.h"
#include "checks_verilog.h"
#include "checks_vhdl.h"
#include "checks_vala.h"
#include "checks_thrift.h"
#include "checks_smalltalk.h"
#include "checks_apl.h"
#include "checks_awk.h"
#include "checks_forth.h"
#include "checks_idl.h"
#include "checks_opencl.h"
#include "checks_openscad.h"
#include "checks_protobuf.h"
#include "checks_sas.h"
#include "checks_stata.h"
#include "checks_viml.h"
#include "taint.h"
Project*project=NULL;
int(*code_scan_printf)(const char*,...)=printf;
int(*code_scan_fprintf)(FILE*,const char*,...)=fprintf;
void*code_scan_alloc(size_t sz){void*p=malloc(sz);if(!p){fprintf(stderr,"FATAL: allocation of %zu bytes failed\n",sz);exit(EXIT_FAILURE);}return p;}
void*code_scan_calloc(size_t nm,size_t sz){void*p=calloc(nm,sz);if(!p){fprintf(stderr,"FATAL: calloc of %zu*%zu failed\n",nm,sz);exit(EXIT_FAILURE);}return p;}
void*code_scan_realloc(void*p,size_t sz){void*n=realloc(p,sz);if(!n&&sz){fprintf(stderr,"FATAL: realloc of %zu bytes failed\n",sz);exit(EXIT_FAILURE);}return n;}
void code_scan_free(void*p){free(p);}
char*code_scan_strdup(const char*s){if(!s)return NULL;size_t l=strlen(s);char*b=malloc(l+1);if(!b)return NULL;memcpy(b,s,l+1);return b;}
char*code_scan_strndup(const char*s,size_t n){if(!s)return NULL;size_t l=strnlen(s,n);char*b=malloc(l+1);if(!b)return NULL;memcpy(b,s,l);b[l]=0;return b;}
int code_scan_printf_wrap(const char*fmt,...){va_list ap;va_start(ap,fmt);int r=vprintf(fmt,ap);va_end(ap);return r;}
int code_scan_fprintf_wrap(FILE*f,const char*fmt,...){va_list ap;va_start(ap,fmt);int r=vfprintf(f,fmt,ap);va_end(ap);return r;}
int code_scan_snprintf(char*buf,size_t sz,const char*fmt,...){va_list ap;va_start(ap,fmt);int r=vsnprintf(buf,sz,fmt,ap);va_end(ap);return r;}
char*code_scan_concat(const char*a,const char*b){if(!a||!b)return NULL;size_t al=strlen(a),bl=strlen(b);char*r=malloc(al+bl+1);memcpy(r,a,al);memcpy(r+al,b,bl+1);return r;}
int code_scan_starts_with(const char*s,const char*pre){if(!s||!pre)return 0;while(*pre){if(*s!=*pre)return 0;s++;pre++;}return 1;}
int code_scan_ends_with(const char*s,const char*suf){if(!s||!suf)return 0;size_t sl=strlen(s),sul=strlen(suf);if(sul>sl)return 0;return memcmp(s+sl-sul,suf,sul)==0;}
char*code_scan_trim(char*s){if(!s)return s;while(*s&&(*s==' '||*s=='\t'||*s=='\n'))s++;char*e=s+strlen(s)-1;while(e>s&&(*e==' '||*e=='\t'||*e=='\n'))e--;*(e+1)=0;return s;}
char*code_scan_lower(char*s){if(!s)return NULL;for(char*p=s;*p;p++)if(*p>='A'&&*p<='Z')*p+='a'-'A';return s;}
int code_scan_str_eq(const char*a,const char*b){if(!a&&!b)return 1;if(!a||!b)return 0;return strcmp(a,b)==0;}
int code_scan_str_len(const char*s){return s?(int)strlen(s):0;}
long long code_scan_file_size(const char*path){struct stat st;if(stat(path,&st)!=0)return -1;return st.st_size;}
char*code_scan_read_file(const char*path,long long*size){FILE*f=fopen(path,"rb");if(!f)return NULL;fseek(f,0,SEEK_END);long long sz=ftell(f);if(sz<0){fclose(f);return NULL;}rewind(f);char*buf=malloc((size_t)sz+1);if(!buf){fclose(f);return NULL;}size_t r=fread(buf,1,(size_t)sz,f);fclose(f);buf[r]=0;if(size)*size=r;return buf;}
const char*lang_str[]={"Unknown","C","C++","Header","C#","Java","JavaScript","TypeScript","Python","Ruby","PHP","Go","Rust","Swift","Kotlin","Scala","Dart","Haskell","Lua","R","Julia","Perl","Shell","SQL","HTML","CSS","YAML","Markdown","XML","Objective-C","Groovy","Fortran","COBOL","BASIC","Pascal","Ada","Lisp","Prolog","Erlang","Elixir","Clojure","F#","Visual Basic","PowerShell","MATLAB","D","Dockerfile","JSON","TOML","CMake","Makefile","TeX","Vue","Svelte","Solidity","GraphQL","Tcl","CoffeeScript","Nim","Zig","OCaml","PureScript","Racket","Scheme","Verilog","VHDL","Vala","Thrift","Smalltalk","APL","Awk","Forth","IDL","OpenCL","OpenSCAD","Protocol Buffers","SAS","Stata","VimL"};
Language code_scan_detect_language(const char*path){const char*fname=strrchr(path,'/');fname=fname?fname+1:path;{if(strcmp(fname,"Makefile")==0||strcmp(fname,"makefile")==0||strcmp(fname,"GNUmakefile")==0)return LANG_MAKEFILE;}{if(strcmp(fname,"CMakeLists.txt")==0)return LANG_CMAKE;}{if(strcasecmp(fname,"Dockerfile")==0)return LANG_DOCKERFILE;}{if(strcmp(fname,"IDL")==0)return LANG_IDL;}const char*e=strrchr(path,'.');if(!e)return LANG_UNKNOWN;e++;if(strcmp(e,"c")==0)return LANG_C;if(strcmp(e,"h")==0)return LANG_HEADER;if(strcmp(e,"hh")==0||strcmp(e,"hpp")==0||strcmp(e,"hxx")==0)return LANG_HEADER;if(strcmp(e,"cpp")==0||strcmp(e,"cc")==0||strcmp(e,"cxx")==0)return LANG_CPP;if(strcmp(e,"cs")==0){if(fname&&(strstr(fname,".cs")!=NULL||strcmp(e,"cs")==0))return LANG_CSHARP;}if(strcmp(e,"java")==0)return LANG_JAVA;if(strcmp(e,"js")==0||strcmp(e,"jsx")==0||strcmp(e,"mjs")==0)return LANG_JS;if(strcmp(e,"ts")==0||strcmp(e,"tsx")==0)return LANG_TS;if(strcmp(e,"py")==0||strcmp(e,"pyw")==0)return LANG_PYTHON;if(strcmp(e,"rb")==0||strcmp(e,"erb")==0)return LANG_RUBY;if(strcmp(e,"php")==0||strcmp(e,"phtml")==0)return LANG_PHP;if(strcmp(e,"go")==0)return LANG_GO;if(strcmp(e,"rs")==0)return LANG_RUST;if(strcmp(e,"swift")==0)return LANG_SWIFT;if(strcmp(e,"kt")==0||strcmp(e,"kts")==0)return LANG_KOTLIN;if(strcmp(e,"scala")==0||strcmp(e,"sc")==0)return LANG_SCALA;if(strcmp(e,"dart")==0)return LANG_DART;if(strcmp(e,"hs")==0||strcmp(e,"lhs")==0)return LANG_HASKELL;if(strcmp(e,"lua")==0)return LANG_LUA;if(strcmp(e,"r")==0||strcmp(e,"R")==0)return LANG_R;if(strcmp(e,"jl")==0)return LANG_JULIA;if(strcmp(e,"pl")==0||strcmp(e,"pm")==0||strcmp(e,"t")==0)return LANG_PERL;if(strcmp(e,"sh")==0||strcmp(e,"bash")==0||strcmp(e,"zsh")==0)return LANG_SHELL;if(strcmp(e,"sql")==0)return LANG_SQL;if(strcmp(e,"html")==0||strcmp(e,"htm")==0||strcmp(e,"xhtml")==0)return LANG_HTML;if(strcmp(e,"css")==0||strcmp(e,"scss")==0||strcmp(e,"less")==0)return LANG_CSS;if(strcmp(e,"yaml")==0||strcmp(e,"yml")==0)return LANG_YAML;if(strcmp(e,"md")==0||strcmp(e,"markdown")==0)return LANG_MARKDOWN;if(strcmp(e,"xml")==0||strcmp(e,"xsd")==0||strcmp(e,"xsl")==0||strcmp(e,"xslt")==0)return LANG_XML;if(strcmp(e,"m")==0||strcmp(e,"mm")==0)return LANG_OBJECTIVEC;if(strcmp(e,"groovy")==0||strcmp(e,"grt")==0||strcmp(e,"gradle")==0)return LANG_GROOVY;if(strcmp(e,"f")==0||strcmp(e,"for")==0||strcmp(e,"f90")==0||strcmp(e,"f95")==0||strcmp(e,"f03")==0)return LANG_FORTRAN;if(strcmp(e,"cbl")==0||strcmp(e,"cob")==0)return LANG_COBOL;if(strcmp(e,"bas")==0||strcmp(e,"BAS")==0)return LANG_BASIC;if(strcmp(e,"pas")==0||strcmp(e,"pp")==0)return LANG_PASCAL;if(strcmp(e,"ada")==0||strcmp(e,"ads")==0)return LANG_ADA;if(strcmp(e,"lisp")==0||strcmp(e,"lsp")==0||strcmp(e,"l")==0||strcmp(e,"cl")==0)return LANG_LISP;if(strcmp(e,"erl")==0)return LANG_ERLANG;if(strcmp(e,"ex")==0||strcmp(e,"exs")==0)return LANG_ELIXIR;if(strcmp(e,"clj")==0||strcmp(e,"cljs")==0||strcmp(e,"cljc")==0)return LANG_CLOJURE;if(strcmp(e,"fs")==0||strcmp(e,"fsx")==0)return LANG_FSHARP;if(strcmp(e,"vb")==0||strcmp(e,"vbs")==0)return LANG_VISUALBASIC;if(strcmp(e,"ps1")==0||strcmp(e,"psm1")==0||strcmp(e,"psd1")==0)return LANG_POWERSHELL;if(strcmp(e,"d")==0)return LANG_D;if(strcmp(e,"json")==0)return LANG_JSON;if(strcmp(e,"toml")==0)return LANG_TOML;if(strcmp(e,"tex")==0||strcmp(e,"sty")==0||strcmp(e,"cls")==0||strcmp(e,"bib")==0)return LANG_TEX;if(strcmp(e,"vue")==0)return LANG_VUE;if(strcmp(e,"svelte")==0)return LANG_SVELTE;if(strcmp(e,"sol")==0)return LANG_SOLIDITY;if(strcmp(e,"graphql")==0||strcmp(e,"gql")==0)return LANG_GRAPHQL;if(strcmp(e,"tcl")==0)return LANG_TCL;if(strcmp(e,"coffee")==0)return LANG_COFFEESCRIPT;if(strcmp(e,"nim")==0)return LANG_NIM;if(strcmp(e,"zig")==0)return LANG_ZIG;if(strcmp(e,"ml")==0||strcmp(e,"mli")==0)return LANG_OCAML;if(strcmp(e,"purs")==0)return LANG_PURESCRIPT;if(strcmp(e,"rkt")==0||strcmp(e,"rktl")==0)return LANG_RACKET;if(strcmp(e,"scm")==0||strcmp(e,"ss")==0)return LANG_SCHEME;if(strcmp(e,"v")==0||strcmp(e,"vh")==0||strcmp(e,"sv")==0)return LANG_VERILOG;if(strcmp(e,"vhd")==0||strcmp(e,"vhdl")==0)return LANG_VHDL;if(strcmp(e,"vala")==0||strcmp(e,"vapi")==0)return LANG_VALA;if(strcmp(e,"thrift")==0)return LANG_THRIFT;if(strcmp(e,"st")==0)return LANG_SMALLTALK;if(strcmp(e,"apl")==0)return LANG_APL;if(strcmp(e,"awk")==0)return LANG_AWK;if(strcmp(e,"fth")==0||strcmp(e,"4th")==0)return LANG_FORTH;if(strcmp(e,"proto")==0)return LANG_PROTOBUF;if(strcmp(e,"sas")==0)return LANG_SAS;if(strcmp(e,"do")==0||strcmp(e,"ado")==0||strcmp(e,"dta")==0)return LANG_STATA;if(strcmp(e,"vim")==0)return LANG_VIML;if(strcmp(e,"matlab")==0)return LANG_MATLAB;if(strcmp(e,"scad")==0)return LANG_OPENSCAD;if(strcmp(e,"cmake")==0)return LANG_CMAKE;{if(strcasecmp(fname,"prolog")==0)return LANG_PROLOG;}{if(strcmp(fname,"idl")==0||strcmp(fname,"IDL")==0)return LANG_IDL;}{if(strcmp(fname,"opencl")==0)return LANG_OPENCL;}return LANG_UNKNOWN;}
int code_scan_is_source_file(const char*path){Language l=code_scan_detect_language(path);return l!=LANG_UNKNOWN;}
void code_scan_error(const char*fmt,...){va_list ap;va_start(ap,fmt);fprintf(stderr,"[ERROR] ");vfprintf(stderr,fmt,ap);fprintf(stderr,"\n");va_end(ap);}
void code_scan_warn(const char*fmt,...){va_list ap;va_start(ap,fmt);fprintf(stderr,"[WARN] ");vfprintf(stderr,fmt,ap);fprintf(stderr,"\n");va_end(ap);}
void code_scan_info(const char*fmt,...){va_list ap;va_start(ap,fmt);printf("[INFO] ");vprintf(fmt,ap);printf("\n");va_end(ap);}
void code_scan_debug(const char*fmt,...){va_list ap;va_start(ap,fmt);printf("[DEBUG] ");vprintf(fmt,ap);printf("\n");va_end(ap);}
IntArray*int_array_new(int cap){IntArray*a=malloc(sizeof(IntArray));a->cap=cap>0?cap:16;a->data=malloc(a->cap*sizeof(int));a->len=0;return a;}
void int_array_add(IntArray*a,int v){if(a->len>=a->cap){a->cap*=2;a->data=realloc(a->data,a->cap*sizeof(int));}a->data[a->len++]=v;}
void int_array_free(IntArray*a){if(a){free(a->data);free(a);}}
StrArray*str_array_new(int cap){StrArray*a=malloc(sizeof(StrArray));a->cap=cap>0?cap:16;a->data=malloc(a->cap*sizeof(char*));a->len=0;return a;}
void str_array_add(StrArray*a,char*s){if(a->len>=a->cap){a->cap*=2;a->data=realloc(a->data,a->cap*sizeof(char*));}a->data[a->len++]=s?code_scan_strdup(s):NULL;}
void str_array_free(StrArray*a){if(a){for(int i=0;i<a->len;i++)free(a->data[i]);free(a->data);free(a);}}
Buffer*buffer_new(long long cap){Buffer*b=malloc(sizeof(Buffer));b->cap=cap>0?(size_t)cap:4096;b->data=malloc(b->cap);b->data[0]=0;b->len=0;return b;}
void buffer_append(Buffer*b,const char*data,long long len){if(!b||!data||len<=0)return;while((size_t)(b->len+len+1)>b->cap){b->cap*=2;b->data=realloc(b->data,b->cap);}memcpy(b->data+b->len,data,(size_t)len);b->len+=len;b->data[b->len]=0;}
void buffer_append_str(Buffer*b,const char*s){if(s)buffer_append(b,s,(long long)strlen(s));}
void buffer_printf(Buffer*b,const char*fmt,...){va_list ap;va_start(ap,fmt);char tmp[8192];vsnprintf(tmp,sizeof(tmp),fmt,ap);va_end(ap);buffer_append_str(b,tmp);}
void buffer_free(Buffer*b){if(b){free(b->data);free(b);}}
char*buffer_detach(Buffer*b){if(!b)return NULL;char*r=b->data;free(b);return r;}
static SourceFile*load_source_file(const char*path){SourceFile*f=calloc(1,sizeof(SourceFile));if(!f)return NULL;snprintf(f->path,sizeof(f->path),"%s",path);{const char*p=strrchr(path,'/');snprintf(f->name,sizeof(f->name),"%s",p?p+1:path);}f->lang=code_scan_detect_language(path);f->content=code_scan_read_file(path,&f->size);if(!f->content){code_scan_error("Cannot read file: %s",path);free(f);return NULL;}LexerState ls;lexer_init(&ls,f->content,path);f->tokens=calloc(MTHOS_MAX_TOKENS,sizeof(Token));f->ntokens=lexer_tokenize(&ls,f->tokens,MTHOS_MAX_TOKENS);f->nissues=0;f->issues=calloc(MTHOS_MAX_ISSUES,sizeof(Issue));f->nincludes=0;f->includes=calloc(MTHOS_MAX_INCLUDES,sizeof(char*));{char*inc=NULL;long long i;for(int i=0;i<f->size;i++){if(f->content[i]=='#'&&strncmp(&f->content[i],"#include",8)==0){long long start=i;while(i<f->size&&f->content[i]!='\n')i++;char*s=code_scan_strndup(&f->content[start],(size_t)(i-start));if(s&&f->nincludes<MTHOS_MAX_INCLUDES)f->includes[f->nincludes++]=s;}if(i>=f->size)break;}}{char*content=f->content;long long sz=f->size;for(long long i=0;i<sz;i++){if(content[i]=='#'){if(strncmp(&content[i],"#ifndef",7)==0){char*start=&content[i+8];while(*start==' '||*start=='\t')start++;char*end=start;while(*end&&*end!='\n'&&*end!=' '&&*end!='\t')end++;size_t len=(size_t)(end-start);if(len>0&&len<sizeof(f->include_guard)){memcpy(f->include_guard,start,len);f->include_guard[len]=0;}break;}}if(content[i]=='\n'&&i>5){char*start=&content[i-5];if(strncmp(start,"#ifndef",7)==0&&start>=content){char*g=start+8;while(*g==' '||*g=='\t')g++;char*e=g;while(*e&&*e!='\n'&&*e!=' '&&*e!='\t')e++;size_t len=(size_t)(e-g);if(len>0&&len<sizeof(f->include_guard)){memcpy(f->include_guard,g,len);f->include_guard[len]=0;}break;}}}}ParserState ps;parser_init(&ps,f->tokens,f->ntokens,f);f->ast=parser_parse(&ps);f->parsed=1;return f;}
int main(int argc,char**argv){Config cfg;config_init(&cfg);int r=config_parse(&cfg,argc,argv);if(r==0)return 0;if(r<0)return 1;if(!config_validate(&cfg)){code_scan_error("Invalid configuration");return 1;}if(cfg.verbose)config_print(&cfg);project=calloc(1,sizeof(Project));project->check_level=cfg.check_level;project->enable_all=cfg.enable_all;project->max_depth=cfg.max_depth;project->max_func_len=cfg.max_func_len;project->max_params=cfg.max_params;project->threads=cfg.threads;project->verbose=cfg.verbose;project->start_time=time(NULL);if(cfg.project_name[0])snprintf(project->project_name,sizeof(project->project_name),"%s",cfg.project_name);else{const char*p=strrchr(cfg.root,'/');snprintf(project->project_name,sizeof(project->project_name),"%s",p?p+1:cfg.root);}char*real=code_scan_alloc(CODE_SCAN_MAX_PATH);if(realpath(cfg.root,real))snprintf(project->root_path,sizeof(project->root_path),"%s",real);free(real);code_scan_printf("Code-Scan Static Analyzer v%s\n",CODE_SCAN_VERSION);code_scan_printf("Copyright (C) 2026 XPDevs. All rights reserved.\n");code_scan_printf("Analyzing project: %s\n",project->project_name);code_scan_printf("Root directory: %s\n",project->root_path);Walker walker;walker_init(&walker);walker_add_dir(&walker,cfg.root);walker.recursive=cfg.recursive;walker.follow_symlinks=cfg.follow_symlinks;for(int i=0;i<cfg.nignore;i++)walker_add_ignore(&walker,cfg.ignore_dirs[i]);code_scan_printf("Scanning for source files...\n");walker_walk(&walker);code_scan_printf("Found %d source files\n",walker.nfiles);if(walker.nfiles==0){code_scan_error("No source files found");return 1;}project->nfiles=walker.nfiles;project->files=calloc((size_t)project->nfiles,sizeof(SourceFile*));project->total_files=walker.nfiles;for(int i=0;i<walker.nfiles;i++){code_scan_printf("  [%d/%d] Loading %s\n",i+1,walker.nfiles,walker.files[i]);SourceFile*f=load_source_file(walker.files[i]);if(f){project->files[i]=f;project->total_lines+=util_count_lines(f->content,f->size);project->total_tokens+=f->ntokens;if(f->ast){int funcs=0;for(int j=0;j<ast_nchildren(f->ast);j++){ASTNode*child=ast_child(f->ast,j);if(child&&child->type==AST_FUNC_DEF)funcs++;}project->total_functions+=funcs;}}else{code_scan_warn("Failed to load: %s",walker.files[i]);}}code_scan_printf("Loaded %d files, %d lines, %d tokens\n",project->nfiles,project->total_lines,project->total_tokens);code_scan_printf("Initializing analysis engine...\n");Engine*engine=engine_init(cfg.threads);engine->verbose=cfg.verbose;engine_register_all(engine);code_scan_printf("Running %d checks across %d files...\n",engine->nchecks,project->nfiles);engine_analyze_project(engine,project);code_scan_printf("Analysis complete. Found %d issues.\n",engine->total_issues);if(cfg.verbose)engine_print_stats(engine);code_scan_printf("Generating report...\n");ReportConfig rcfg;memset(&rcfg,0,sizeof(rcfg));if(cfg.output[0])snprintf(rcfg.path,sizeof(rcfg.path),"%s",cfg.output);rcfg.format=cfg.json?1:(cfg.html?2:0);rcfg.verbose=cfg.verbose;rcfg.include_suggestions=cfg.show_suggestions;rcfg.include_context=cfg.show_context;rcfg.max_issues=cfg.max_issues;int out_len=0;char*report=reporter_generate(project,&rcfg,&out_len);if(report){if(cfg.output[0]){if(util_write_file(cfg.output,report,(long long)out_len)){code_scan_printf("Report written to %s (%d bytes)\n",cfg.output,out_len);}else{code_scan_error("Failed to write report to %s",cfg.output);printf("%s",report);}}else{printf("%s",report);}free(report);}else{code_scan_error("Failed to generate report");}if(cfg.verbose){code_scan_printf("\nAnalysis time: %.3f seconds\n",project->analysis_time);time_t now=time(NULL);double elapsed=difftime(now,project->start_time);code_scan_printf("Total wall time: %.0f seconds\n",elapsed);}for(int i=0;i<project->nfiles;i++){if(project->files[i]){free(project->files[i]->content);free(project->files[i]->tokens);free(project->files[i]->issues);for(int j=0;j<project->files[i]->nincludes;j++)free(project->files[i]->includes[j]);free(project->files[i]->includes);if(project->files[i]->ast)ast_free_deep(project->files[i]->ast);free(project->files[i]);}}free(project->files);engine_free(engine);walker_free(&walker);free(project);return 0;}
