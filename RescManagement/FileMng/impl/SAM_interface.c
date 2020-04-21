#include "../SAM_interface.h"

void initMappedRead(MAPPED_READ* mapped_read) {
	//initialize defaults
	mapped_read->Rnext[0] = '*';
	mapped_read->Pnext = 0;
	mapped_read->Tlen = 0;
}

void writeSamLine(FILE* fp, MAPPED_READ mapped_read) {

	fprintf(fp, "%s\t", mapped_read.read.Qname);
	fprintf(fp, "%i\t", mapped_read.Flag);
	fprintf(fp, "%s\t", mapped_read.Rname);
	fprintf(fp, "%i\t", mapped_read.Pos);
	fprintf(fp, "%i\t", mapped_read.MapQ);
	fprintf(fp, "%s\t", mapped_read.CIGAR);
	fprintf(fp, "%s\t", mapped_read.Rnext);
	fprintf(fp, "%i\t", mapped_read.Pnext);
	fprintf(fp, "%i\t", mapped_read.Tlen);

	//print sequence
	for (SEQ_INDEX i = 0; i < mapped_read.read.seq.length; i++) {
		fputc(baseToChar(mapped_read.read.seq.el[i]), fp);
	}
	fputc('\t', fp);

	fprintf(fp, "%s\t", mapped_read.read.qualities);

	fprintf(fp, "\n");
}
