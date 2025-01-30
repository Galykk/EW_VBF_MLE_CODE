
//Will allow Qsigex classes to be viewed by Root
{
printf("Qsigex will work on ROOT\n");
gInterpreter->AddIncludePath("-I$QSIGEXDIR/include");
gSystem->Load("$QSIGEXDIR/lib/libqsigex2.so");
}