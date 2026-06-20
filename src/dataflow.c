/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#include "code_scan.h"
#include "dataflow.h"
DFGraph*df_build(CFGraph*cfg,ASTNode*func){DFGraph*df=calloc(1,sizeof(DFGraph));if(!df)return NULL;df->cfg=cfg;df->cap=cfg?cfg->nblocks:64;df->blocks=calloc(df->cap,sizeof(DFBlock*));if(!df->blocks){free(df);return NULL;}for(int i=0;i<df->cap;i++){DFBlock*db=calloc(1,sizeof(DFBlock));if(!db)continue;db->id=i;db->stmt=NULL;db->in=df_set_new(256);db->out=df_set_new(256);db->gen=df_set_new(256);db->kill=df_set_new(256);if(cfg&&i<cfg->nblocks)db->stmt=cfg->blocks[i]->start;df->blocks[df->nblocks++]=db;}return df;}
DFSet*df_set_new(int size){DFSet*s=calloc(1,sizeof(DFSet));if(!s)return NULL;s->set_size=size;int bytes=(size+7)/8;s->defs=calloc(bytes,1);s->uses=calloc(bytes,1);s->in_set=calloc(bytes,1);s->out_set=calloc(bytes,1);s->gen_set=calloc(bytes,1);s->kill_set=calloc(bytes,1);return s;}
void df_set_add(DFSet*s,int v){if(!s||v<0||v>=s->set_size)return;int byte=v/8;int bit=v%8;s->defs[byte]|=(1<<bit);}
int df_set_contains(DFSet*s,int v){if(!s||v<0||v>=s->set_size)return 0;int byte=v/8;int bit=v%8;return(s->defs[byte]>>bit)&1;}
void df_set_union(DFSet*a,DFSet*b){if(!a||!b)return;int bytes=(a->set_size+7)/8;for(int i=0;i<bytes;i++)a->defs[i]|=b->defs[i];}
void df_set_intersect(DFSet*a,DFSet*b){if(!a||!b)return;int bytes=(a->set_size+7)/8;for(int i=0;i<bytes;i++)a->defs[i]&=b->defs[i];}
void df_set_copy(DFSet*dst,DFSet*src){if(!dst||!src)return;int bytes=(dst->set_size+7)/8;memcpy(dst->defs,src->defs,bytes);}
void df_set_clear(DFSet*s){if(!s)return;int bytes=(s->set_size+7)/8;memset(s->defs,0,bytes);}
int df_set_equal(DFSet*a,DFSet*b){if(!a&&!b)return 1;if(!a||!b)return 0;int bytes=(a->set_size+7)/8;return memcmp(a->defs,b->defs,bytes)==0;}
void df_reaching_defs(DFGraph*df){if(!df)return;for(int i=0;i<df->nblocks;i++)df_set_clear(df->blocks[i]->in);int changed=1;while(changed){changed=0;for(int i=0;i<df->nblocks;i++){DFBlock*b=df->blocks[i];DFSet*new_in=df_set_new(b->in->set_size);df_set_copy(new_in,b->in);if(b->id>0){DFBlock*pred=df->blocks[b->id-1];df_set_copy(new_in,pred->out);}df_set_union(new_in,b->gen);if(!df_set_equal(new_in,b->in)){df_set_copy(b->in,new_in);changed=1;}DFSet*new_out=df_set_new(b->out->set_size);df_set_copy(new_out,b->in);df_set_union(new_out,b->gen);if(!df_set_equal(new_out,b->out)){df_set_copy(b->out,new_out);changed=1;}free(new_in->defs);free(new_in->uses);free(new_in->in_set);free(new_in->out_set);free(new_in->gen_set);free(new_in->kill_set);free(new_in);free(new_out->defs);free(new_out->uses);free(new_out->in_set);free(new_out->out_set);free(new_out->gen_set);free(new_out->kill_set);free(new_out);}}}
void df_live_vars(DFGraph*df){if(!df)return;int changed=1;while(changed){changed=0;for(int i=df->nblocks-1;i>=0;i--){DFBlock*b=df->blocks[i];DFSet*new_out=df_set_new(b->out->set_size);if(i+1<df->nblocks){DFSet*s=df->blocks[i+1]->in;df_set_copy(new_out,s);}if(!df_set_equal(new_out,b->out)){df_set_copy(b->out,new_out);changed=1;}DFSet*new_in=df_set_new(b->in->set_size);df_set_copy(new_in,b->out);df_set_union(new_in,b->gen);if(!df_set_equal(new_in,b->in)){df_set_copy(b->in,new_in);changed=1;}free(new_in->defs);free(new_in->uses);free(new_in->in_set);free(new_in->out_set);free(new_in->gen_set);free(new_in->kill_set);free(new_in);free(new_out->defs);free(new_out->uses);free(new_out->in_set);free(new_out->out_set);free(new_out->gen_set);free(new_out->kill_set);free(new_out);}}}
void df_available_exprs(DFGraph*df){}
void df_very_busy_exprs(DFGraph*df){}
int df_find_def(DFGraph*df,const char*varname){return-1;}
int df_find_use(DFGraph*df,const char*varname){return-1;}
int df_is_constant(DFGraph*df,const char*varname,int block_id){return 0;}
int df_get_def_count(DFGraph*df,const char*varname){return 0;}
int df_get_block_id(DFGraph*df,ASTNode*stmt){return 0;}
void df_dump(DFGraph*df){if(!df)return;code_scan_printf("DFGraph: %d blocks\n",df->nblocks);for(int i=0;i<df->nblocks;i++){DFBlock*b=df->blocks[i];code_scan_printf("  B%d:",i);code_scan_printf(" in=");for(int j=0;j<16;j++)code_scan_printf("%d",df_set_contains(b->in,j));code_scan_printf(" out=");for(int j=0;j<16;j++)code_scan_printf("%d",df_set_contains(b->out,j));code_scan_printf("\n");}}
void df_free(DFGraph*df){if(!df)return;for(int i=0;i<df->nblocks;i++){if(df->blocks[i]){free(df->blocks[i]->in);free(df->blocks[i]->out);free(df->blocks[i]->gen);free(df->blocks[i]->kill);free(df->blocks[i]);}}free(df->blocks);free(df);}
