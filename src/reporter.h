/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef REPORTER_H
#define REPORTER_H
#include "code_scan.h"
typedef struct{char path[CODE_SCAN_MAX_PATH];int format;int verbose;int include_suggestions;int include_context;int max_issues;}ReportConfig;
typedef struct{Buffer*buf;int total_issues;int total_files;int total_lines;int total_security;int total_memory;int total_syntax;int total_type;int total_perf;int total_concurrency;int total_quality;int total_buf;int total_critical;int total_error;int total_warning;int total_info;double score;double security_score;double quality_score;}ReportData;
char*reporter_generate(Project*p,ReportConfig*cfg,int*out_len);void reporter_text_report(ReportData*rd,Project*p,Buffer*b);void reporter_json_report(ReportData*rd,Project*p,Buffer*b);void reporter_html_report(ReportData*rd,Project*p,Buffer*b);void reporter_summary(ReportData*rd,Project*p,Buffer*b);void reporter_breakdown(ReportData*rd,Buffer*b);void reporter_score(ReportData*rd,Buffer*b);ReportData*reporter_compute(Project*p);
#endif
