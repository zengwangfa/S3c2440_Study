�������Makefile��Ϊ3��:
1. ����Ŀ¼��Makefile
2. ����Ŀ¼��Makefile.build
3. ������Ŀ¼��Makefile

һ��������Ŀ¼��Makefile��
   ����򵥣���ʽ���£�
obj-y += file.o
obj-y += subdir/
   
   "obj-y += file.o"��ʾ�ѵ�ǰĿ¼�µ�file.c��������
   "obj-y += subdir/"��ʾҪ����subdir�����Ŀ¼��ȥѰ���ļ���������������Щ�ļ���subdirĿ¼�µ�Makefile������

ע��: "subdir/"�е�б��"/"����ʡ��

��������Ŀ¼��Makefile��
   �����˶���obj-y��ָ����Ŀ¼��Ҫ�������ȥ���ļ�����Ŀ¼�⣬��Ҫ�Ƕ��幤������������������Ӳ������������ļ�����export�����ĸ�������

��������Ŀ¼��Makefile.build��
   ������ӵĲ��֣����Ĺ��ܾ��ǰ�ĳ��Ŀ¼������������Ŀ¼�С���Ҫ�������ȥ���ļ���������������Ϊbuilt-in.o
   ��ϸ�Ľ����뿴��Ƶ��

�ġ���ôʹ������Makefile��
1���Ѷ���Makefile, Makefile.build�������Ķ���Ŀ¼
2���޸Ķ���Makefile
2.1 �޸Ĺ�����
2.2 �޸ı���ѡ�����ѡ��
2.3 �޸�obj-y��������Ŀ¼����Щ�ļ�����Щ��Ŀ¼���������
2.4 �޸�TARGET����������ָ����������ĳ��������

3. �ڸ�һ����Ŀ¼�¶���һ��Makefile����ʽΪ��
obj-y += file1.o
obj-y += file2.o
obj-y += subdir1/
obj-y += subdir2/

4. ִ��"make"�����룬ִ��"make clean"�������ִ��"make distclean"���������
   
   