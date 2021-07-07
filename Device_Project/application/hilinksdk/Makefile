#=======================================================================================
#外部Makefile文件修改参考
#请在对应字段下添加以下内容,-lhilinkot选项根据实际情况添加
#SUBDIRS += (hilinksdk path)/hilinksdk
#COMPONENTS_eagle.app.v6 += (hilinksdk path)/hilinksdk/libhilinksdk.a
#EXTRA_LIBS += -L (hilinksdk path)/hilinksdk/lib -lhilinkdevicesdk -lhilinkota
#INCLUDES += -I (hilinksdk path)/hilinksdk/include
#=======================================================================================
ifndef PDIR
GEN_LIBS = libhilinksdk.a
endif

INCLUDES := $(INCLUDES) -I $(PDIR)include
INCLUDES += -I ./include

PDIR := ../$(PDIR)
sinclude $(PDIR)Makefile