<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>URL-Filter | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base-proxy.php" title="12. Kapitel - Proxy"><link rel="prev" href="base-proxy-configuration.php" title="12.3. Proxykonfiguration"><link rel="next" href="base-proxy-content.php" title="12.5. Web-Content Filter">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="base-proxy-url.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-proxy-url.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">12.4. URL-Filter</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-proxy-configuration.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">12. Kapitel - Proxy</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-proxy-content.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-proxy-url"></a>12.4. URL-Filter</h2></div></div></div><a class="indexterm" name="base-proxy-url1"></a><a class="indexterm" name="base-proxy-url2"></a><a class="indexterm" name="base-proxy-url-profile"></a><p>Der URL-Filter kann Seiten anhand der URL oder IP sperren. Die Zugriffskontrolle geschieht
      &uuml;ber Proxy-Profile. Diese werden entweder dem Netzwerkobjekt direkt (siehe <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-intranet-rights.php">Abschnitt&nbsp;9.2, &#8222;Zugriffsrechte eines Netzwerkobjekts&#8220;</a>), oder bei
      Proxy-Authentifizierung &uuml;ber die Rechte des angemeldeten Benutzers (siehe <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-user-manager.php#base-user-manager-groups-rights">Abschnitt&nbsp;14.1.1, &#8222;Zugriffsrechte&#8220;</a>)
      zugewiesen.</p><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-proxy-url-profiles"></a>12.4.1. Proxy-Profile</h3></div></div></div><a class="indexterm" name="base-proxy-url-accesslist"></a><p>Proxy-Profile werden unter
        Dienste&nbsp;&gt;&nbsp;Proxy&nbsp;&gt;&nbsp;Profile konfiguriert. In
        einem Profil werden mehrere Proxy-Zugriffslisten zusammengefasst.</p><p>F&uuml;r das Zusammenfassen gelten folgende Regeln: </p><div class="itemizedlist"><ul type="disc"><li><p>Werden mehrere Sperrlisten (gekennzeichnet mit &#8222;-&#8220;) zusammengefasst, sind alle
              ihre Seiten gesperrt</p></li><li><p>Werden mehrere Freigabelisten (gekennzeichnet mit &#8222;+&#8220;) zusammengefasst, sind alle
              Seiten gesperrt, die nicht in mindestens einer Freigabeliste enthalten sind</p></li><li><p>Werden Freigabelisten und Sperrlisten zusammengefasst, sind alle in den
              Sperrlisten enthaltenen Seiten gesperrt. Ist eine Seite sowohl in einer Freigabeliste
              als auch in einer Sperrliste enthalten, so ist sie freigegeben</p></li></ul></div><p>
      </p><a class="indexterm" name="d0e2906"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-proxy-url-accesslists"></a>12.4.2. Proxy-Zugriffslisten</h3></div></div></div><p>Zugriffslisten werden unter
        Dienste&nbsp;&gt;&nbsp;Proxy&nbsp;&gt;&nbsp;Zugriffslisten
        verwaltet. Eine Zugriffsliste kann entweder hochgeladen (f&uuml;r gro&szlig;e Listen), direkt im
        Browser editiert werden (f&uuml;r kleinere Listen) oder vordefiniert sein. Au&szlig;erdem gibt es 3
        verschiedene Listentypen:</p><div class="informaltable"><table border="1"><colgroup><col align="left"><col align="left"></colgroup><tbody><tr><td align="left">Domain oder URL</td><td align="left">hier wird eine komplette Domain oder eine URL gesperrt (oder freigegeben).
                Beispiel: &#8222;www.sex.com/offer&#8220; &#8211; hier wird der Zugriff auf www.sex.com/offer explizit
                gesperrt, nicht aber z.B. auf www.sex.com/free</td></tr><tr><td align="left">Wildcard</td><td align="left">hier kann das bekannte Wildcard-Zeichen &#8222;*&#8220; verwendet werden um Teile der URL
                zu erkennen. Beispiel: &#8222;*.mp3&#8220; &#8211; sperrt den Zugriff auf alle URLs bei denen am
                Schluss &#8222;.mp3&#8220; steht; &#8222;*sex*&#8220; &#8211; sperrt den Zugriff auf alle URLs die irgendwo &#8222;sex&#8220;
                enthalten</td></tr><tr><td align="left">Regular Expression</td><td align="left">die URLs werden durch POSIX regular expressions gepr&uuml;ft. F&uuml;r Experten, die
                wissen, was sie tun</td></tr></tbody></table></div><p>Wurde unter
        Dienste&nbsp;&gt;&nbsp;Proxy&nbsp;&gt;&nbsp;Einstellungen die Option
          <span class="guimenuitem">IP-Adressen der URLs sperren</span> aktiviert, so werden alle
        Domainnamen in den Zugriffslisten aufgel&ouml;st und die dazugeh&ouml;rigen IPs auch gesperrt. Damit
        ist es nicht m&ouml;glich, den URL-Filter durch Eingabe einer IP zu umgehen.</p><a class="indexterm" name="d0e2937"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-proxy-url-timecontrol"></a>12.4.3. Zeitsteuerung</h3></div></div></div><a class="indexterm" name="base-proxy-url-timecontrol1"></a><p>Es ist m&ouml;glich, den Proxy so zu konfigurieren, dass er abh&auml;ngig von Tageszeit und
        Wochentag unterschiedliche Seiten sperrt bzw. freigibt. Damit k&ouml;nnen z.B. au&szlig;erhalb der
        regul&auml;ren Arbeitszeit oder in Pausenzeiten privat genutzte Webseiten freigegeben
        werden.</p><p>Definieren Sie dazu zuerst unter
        Dienste&nbsp;&gt;&nbsp;Proxy&nbsp;&gt;&nbsp;Zeiten die gew&uuml;nschten
        Zeitr&auml;ume. Bei der Verwendung von Sperrlisten empfehlen wir, ein Zeitprofil f&uuml;r die
        eingeschr&auml;nkteren Uhrzeiten (z.B. "Kernarbeitszeit") anzulegen.</p><p>Danach k&ouml;nnen Sie unter
        Dienste&nbsp;&gt;&nbsp;Proxy&nbsp;&gt;&nbsp;Profile ein Profil so
        zusammenstellen, dass einige der Zugriffslisten nur zu bestimmten Uhrzeiten gelten. W&auml;hlen
        Sie daf&uuml;r in dem Dropdown-Men&uuml; <span class="guimenuitem">Zeitprofil</span> zuerst das passende
        aus, w&auml;hlen dann die entsprechende Zugriffsliste und klicken dann auf
          <span class="guibutton">&lt;</span> um sie zum Profil hizuzuf&uuml;gen.</p><p>Wenn beispielsweise Erotik-Seiten nie erreichbar sein sollen, Webmail-Dienste dagegen nur
        au&szlig;erhalb der Kernarbeitszeit, dann f&uuml;gen Sie die Zugriffsliste Erotik mit dem Zeitprofil
          <code class="option">Jederzeit</code>, die Zugriffsliste Mail dagegen mit dem Zeitprofil
        <code class="option">Kernarbeitszeit</code> hinzu.</p><p>Beachten Sie, dass ein Proxy-Profil immer nur 2 verschiedene Zeitbl&ouml;cke enthalten kann:
          <code class="option">Jederzeit</code> und eines der definierbaren Zeitprofile.</p><a class="indexterm" name="d0e2971"></a><a class="indexterm" name="d0e2972"></a><a class="indexterm" name="d0e2973"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-proxy-configuration.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base-proxy.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-proxy-content.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">12.3. Proxykonfiguration&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;12.5. Web-Content Filter</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>