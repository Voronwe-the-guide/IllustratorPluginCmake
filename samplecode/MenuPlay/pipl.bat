echo "Create Pipl"

c:\Python27\python2.exe ..\..\tools\pipl\create_pipl.py -input "[{\"name\":\"MenuPlay\",\"entry_point\" : \"PluginMain\"}]"

::c:\Python27\python2.exe ..\3rdParty\AdobeSDK\tools\pipl\create_pipl.py -input "[{\"name\":\"GMGIllustratorPlugin\"}]"

echo "move plugin.pipl to Resources\Win"

move plugin.pipl Resources/Win/