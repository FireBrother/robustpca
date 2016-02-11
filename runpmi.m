load ./WestburyLab.Wikipedia.Corpus.pmi.txt;
load ./WestburyLab.Wikipedia.Corpus.topKfreq.txt;
raw=WestburyLab_Wikipedia_Corpus_pmi;
wordlist=WestburyLab_Wikipedia_Corpus_topKfreq;
clear WestburyLab_Wikipedia_Corpus_pmi;
clear WestburyLab_Wikipedia_Corpus_topKfreq;
table=java.util.HashMap;
for i=1:5000
    table.put(wordlist(i,1),i);
end;
for i=1:length(raw(:,1))
    raw(i,1)=table.get(raw(i,1));
    raw(i,2)=table.get(raw(i,2));
end;
pmi_s(:,1) = [raw(:,1); raw(:,2)];
pmi_s(:,2) = [raw(:,2); raw(:,1)];
pmi_s(:,3) = [raw(:,3); raw(:,3)];
pmi=sparse(pmi_s(:,1),pmi_s(:,2),pmi_s(:,3));
pmi=max(pmi,0);
pmi = pmi.*(~eye(5000));
[A_hat,E_hat,iter]=inexact_alm_rpca(pmi,0.05,1e-5,1000);
[U S V]=svd(A_hat);

outputbuff(:,1) = wordlist(:,1);
outputbuff(:,2:101) = U(:,1:100);
dlmwrite('vectors.txt',outputbuff,' ');
