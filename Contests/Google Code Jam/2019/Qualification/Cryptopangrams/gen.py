prime_list = [2074722246773485207821695222107608587480996474721117292752992589912196684750549658310084416732550077,
              2367495770217142995264827948666809233066409497699870112003149352380375124855230068487109373226251983,
              1814159566819970307982681716822107016038920170504391457462563485198126916735167260215619523429714031,
              5371393606024775251256550436773565977406724269152942136415762782810562554131599074907426010737503501,
              6513516734600035718300327211250928237178281758494417357560086828416863929270451437126021949850746381,
              5628290459057877291809182450381238927697314822133923421169378062922140081498734424133112032854812293,
              2908511952812557872434704820397229928450530253990158990550731991011846571635621025786879881561814989,
              2193992993218604310884461864618001945131790925282531768679169054389241527895222169476723691605898517,
              5202642720986189087034837832337828472969800910926501361967872059486045713145450116712488685004691423,
              7212610147295474909544523785043492409969382148186765460082500085393519556525921455588705423020751421,
              282755483533707287054752184321121345766861480697448703443857012153264407439766013042402571,
              370332600450952648802345609908335058273399487356359263038584017827194636172568988257769601,
              463199005416013829210323411514132845972525641604435693287586851332821637442813833942427923,
              374413471625854958269706803072259202131399386829497836277471117216044734280924224462969371,
              664869143773196608462001772779382650311673568542237852546715913135688434614731717844868261,
              309133826845331278722882330592890120369379620942948199356542318795450228858357445635314757,
              976522637021306403150551933319006137720124048624544172072735055780411834104862667155922841,
              635752334942676003169313626814655695963315290125751655287486460091602385142405742365191277,
              625161793954624746211679299331621567931369768944205635791355694727774487677706013842058779,
              204005728266090048777253207241416669051476369216501266754813821619984472224780876488344279,
              40979218404449071854385509743772465043384063785613460568705289173181846900181503,
              56181069873486948735852120493417527485226565150317825065106074926567306630125961,
              19469495355310348270990592580191998639221450743640952620236903851789700309402857,
              34263233064835421125264776608163440537925705997962346596977803462033841059628723,
              14759984361802021245410475928101669395348791811705709117374129427051861355011151,
              67120333368520272532940669112228025474970578938046280618394371551488988323794243]

prime_list = sorted(prime_list)

text = 'CJQUIZKNOWBEVYOFDPFLUXALGORITHMS'

print 1
print 10**100, len(text) - 1
crypt = []
for i in xrange(len(text) - 1):
    crypt.append(prime_list[ord(text[i]) - ord('A')] * prime_list[ord(text[i + 1]) - ord('A')])

print ' '.join(map(str, crypt))
