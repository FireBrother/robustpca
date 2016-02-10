from spacy.en import English
nlp = English(parser=False)
f = open('WestburyLab.Wikipedia.Corpus.txt')
of = open('WestburyLab.Wikipedia.Corpus.token.txt', 'w')
#f = open('test.txt')
#of = open('test_token.txt', 'w')
dof = open('dict.txt', 'w')
for sentence in f:
        tokens = nlp(sentence.decode('ascii', 'ignore'))
        for token in tokens[:-1]:
                of.write('%d ' % token.orth)
        of.write('\n')

print '111'
for word in nlp.vocab:
        dof.write('%d %s\n' % (word.orth, word.orth_.encode('ascii', 'ignore')))
print '222'
