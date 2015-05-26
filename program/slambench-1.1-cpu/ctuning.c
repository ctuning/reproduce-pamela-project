/*

 CK OpenME cTuning plugin

 cTuning plugin is used for fine-grain online application timing and tuning

 OpenME - Event-driven, plugin-based interactive interface to "open up" 
          any software (C/C++/Fortran/Java/PHP) and possibly connect it to cM

 Developer(s): (C) Grigori Fursin
 http://cTuning.org/lab/people/gfursin

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __MINGW32__
# include <sys/time.h>
#else
# ifdef WINDOWS
#  include <time.h>
# else
#  include <sys/time.h>
# endif
#endif

#ifndef OPENME_NTIMERS
# define OPENME_NTIMERS 1
#endif

#ifndef OPENME_NFEATURES
# define OPENME_NFEATURES 0
#endif

#define OPENME_DEBUG "OPENME_DEBUG"

static char* ck_time_file="tmp-ck-timer.json";

#ifdef WINDOWS
static clock_t start[OPENME_NTIMERS];
#else 
static double start[OPENME_NTIMERS];
static struct timeval  before[OPENME_NTIMERS], after;
#endif
static double secs[OPENME_NTIMERS];

static char *env;

static char *features[OPENME_NFEATURES]; 

void clock_start(int timer)
{
#ifdef WINDOWS
  start[timer] = clock();
#else
  #ifdef __INTEL_COMPILERX
    start[timer] = (double)_rdtsc();
  #else
    gettimeofday(&before[timer], NULL);
  #endif
#endif
  if ( ((env = getenv(OPENME_DEBUG)) != NULL) && (atoi(env)==1) )
    printf("OpenME event: start clock\n");

}

void clock_end(int timer)
{
#ifdef WINDOWS
  secs[timer] = ((double)(clock() - start[timer])) / CLOCKS_PER_SEC;
#else
  #ifdef __INTEL_COMPILERX
  secs[timer] = ((double)((double)_rdtsc() - start[timer])) / (double) getCPUFreq();
  #else
  gettimeofday(&after, NULL);
  secs[timer] = (after.tv_sec - before[timer].tv_sec) + (after.tv_usec - before[timer].tv_usec)/1000000.0;
  #endif
#endif
  if ( ((env = getenv(OPENME_DEBUG)) != NULL) && (atoi(env)==1) )
    printf("OpenME event: stop clock: %f\n", secs[timer]);
}

void program_start(void)
{
  int timer;
  int feature;

  if ( ((env = getenv(OPENME_DEBUG)) != NULL) && (atoi(env)==1) )
    printf("OpenME event: start program\n");

  printf("Start program\n");

  for (timer=0; timer<OPENME_NTIMERS; timer++)
  {
    secs[timer] = 0.0;
    start[timer] = 0.0;
  }

  for (feature=0; feature<OPENME_NFEATURES; feature++)
  {

    features[feature]=(char*) malloc(1024*sizeof(char));
    features[feature][0]=0;
  }
}

void xopenme_add_feature_i(int feature, char* desc, int sfeature)
{
  sprintf(features[feature], desc, sfeature);
}

void xopenme_add_feature_f(int feature, char* desc, float sfeature)
{
  sprintf(features[feature], desc, sfeature);
}

void xopenme_add_feature_d(int feature, char* desc, double sfeature)
{
  sprintf(features[feature], desc, sfeature);
}

void xopenme_add_feature_s(int feature, char* desc, void* sfeature)
{
  sprintf(features[feature], desc, sfeature);
}

void xopenme_dump_memory(char* name, void* array, long size)
{
  FILE *fx=fopen(name , "wb" );
  fwrite(array, size, 1, fx);
  fclose(fx);
}

void program_end(void)
{
  FILE* f;
  int timer;
  int feature;

  if ( ((env = getenv(OPENME_DEBUG)) != NULL) && (atoi(env)==1) )
    printf("OpenME event: ending program\n");

  printf("Stop program123\n");

  f=fopen(ck_time_file, "w");
  if (f==NULL)
  {
    printf("Error: can't open timer file %s for writing\n", ck_time_file);
    exit(1);
  }

  fprintf(f,"{\n");

  fprintf(f," \"execution_time\":%.6lf,\n", secs[0]);
  for (timer=0; timer<OPENME_NTIMERS; timer++) 
  {
    fprintf(f," \"execution_time_kernel_%u\":%.6lf", timer, secs[timer]);
    if (timer!=(OPENME_NTIMERS-1) || (OPENME_NFEATURES!=0)) fprintf(f, ",");
    fprintf(f, "\n");
  }

  if (OPENME_NFEATURES>0)
  {
    fprintf(f," \"features\":{\n");
    for (feature=0; feature<OPENME_NFEATURES; feature++) 
    {
      fprintf(f,"  %s", features[feature]);
      if (feature!=(OPENME_NFEATURES-1)) fprintf(f, ",");
      fprintf(f, "\n");
    }
    fprintf(f," }\n");
  }

  fprintf(f,"}\n");

  fclose(f);
}
