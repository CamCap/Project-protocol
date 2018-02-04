<h1 id="vs-">VS를 깃허브에 연동</h1>
<p>데탑을 2주에 걸쳐서 이제 조립을 완성했다... 처음하는 조립이라서 헤맨 부분도 있었지만, 오래걸린 이유는 메인보드 초기불량...<br />아는 형님의 도움을 받아서 조립의 팁을 몇 개받았다. 그 형님이 아니었으면 난 지금쯤 반쯤 정신놓고 아직도 고치고있지 않았을까?<br />뭔가 2주동안 짜증은 났지만 그래도 재미는 있었고, 다음에 또 조립해보고 싶다.</p>
<hr>
<h2 id="-">동기</h2>
<blockquote>
<ol>
<li>집에서는 데탑으로 코딩하고, 밖에서는 노트북으로 코딩하고 싶다. 두 개를 연동해서 어디서든 코딩하고 싶다.</li>
</ol>
</blockquote>
<hr>
<h2 id="-">계획</h2>
<blockquote>
<ol>
<li>일단 마소에서 VSTS로 Git을 지원해주는 것같다. 이걸 이용해보면 될 것같다.</li>
<li>연동이 잘 안되거나 불편하면 그냥 USB나 외장하드에 저장하고 다녀야겠다.</li>
</ol>
</blockquote>
<p>어쩃든간에 어제 하루는 데탑 조립하고 셋팅하는데에 하루를 보냈다. 특히 이번 셋팅에서 신경쓴 부분은 비주얼 스튜디오를 깃허브와 연동하기.<br />가끔 노트북을 들고 밖에 나가서 코딩하기에 연동을 해보기로 했다.  </p>
<hr>
<h2 id="-">난관</h2>
<blockquote>
<ol>
<li>Git에대한 개념이 아예 없이 VSTS로만 연동할려고 했었다. 당연하지만, VSTS도 Git의 한 종류였고, Git을 사용하는 방법을 몰랐다. 연동하는데 필요한 리포지토리를 몰라서 VSTS는 설치했지만 연동하는데 실패.<br />한 바퀴 돌아서 GitHub를 사용하기로 결정. GitBub를 연동하고 난 뒤에 깨달았지만, 굳이 GitHub를 사용할 필요는 없었다. 그냥 VSTS로도 충분히 내 목적을 달성할 수 있었을텐데...</li>
<li>노트북에 GitHub Extension for Visual Studio를 설치하는 도중에 계속 "SignatureDescription could not creadted"라는 오류를 냈다. 찾아보니, 매니페스트 오류라고 하는데, .Net4.5을 설치하면 해결된다고 하더라. 근데 내 노트북은 그 이하였나보더라...결국 닷넷을 설치하는 김에 VS도 2013에서 2017로 업그레이드했다.</li>
</ol>
</blockquote>
<hr>
<h2 id="-">과정</h2>
<p>기본적인 방법은 정말 간단하다. </p>
<blockquote>
<ol>
<li>깃허브에 계정과 프로젝트를 만든다.</li>
<li>깃허브 프로젝트 HTTPS 주소를 복사</li>
<li><strong>VSTS</strong>(Visual Studio Team Service)를 설치한다. </li>
<li>깃허브와 VS을 연동하기위한 <strong>GitHub Extension for Visual Studio</strong>을 설치</li>
<li>비주얼 스튜디오의 팀 탐색기의 설정에서 <strong>리포지토리 설정</strong></li>
<li>원격에서 깃허브의 프로젝트의 HTTPS의 주소를 추가</li>
</ol>
</blockquote>
<p>깃허브에 푸쉬</p>
<blockquote>
<ol>
<li>팀 탐색기에서 동기화 탭에서 푸쉬 탭에서 저장소를 선택한 뒤에 푸쉬를 클릭! 만약 리포지토리에 분기가 존재하지 않는다는 오류가 나오면 <a href="http://son10001.blogspot.kr/2017/06/git-visual-studio-2017-github.html">SonMan's IT BBS</a>를 참고.</li>
</ol>
</blockquote>
<p>깃허브에서 내 로컬 저장소로 받아오기   </p>
<blockquote>
<p style="text-align: center; clear: none; float: none;">[##_1N|cfile25.uf@9957DF395A6555601A5B9A.PNG|width="1170" height="636" filename="cap2.PNG" filemime="image/jpeg"|_##]</p>
<p><br /></p>
<p>7.연결 관리에서 윗 <strong>GitHub</strong>에 깃허브의 프로젝트 HTTPS를 입력하고 아래의 <strong>로컬 Git 리포지트리</strong>에는 로컬에 저장된 경로를 입력하고 Clone을 클릭하면 된다.</p>
</blockquote>
<hr>
<h3 id="-">링크 모음</h3>
<p><a href="https://www.visualstudio.com/ko/team-services">VSTS</a><br /><a href="http://son10001.blogspot.kr/2017/06/git-visual-studio-2017-github.html">SonMan's IT BBS</a><br /><a href="https://visualstudio.github.com">Git for Visual Studio</a><br /><a href="http://diary.virlit.com/31">Visual Studio에서 git hub 익히기</a></p>
<hr><p><br /></p>