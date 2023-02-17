<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>SSL-Verschl&uuml;sselung und Zertifikate | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base.php" title="Teil&nbsp;2.&nbsp;Allgemeine Funktionen"><link rel="prev" href="base-intranet-local-routing.php" title="9.8. Routing im Intranet"><link rel="next" href="base-ssl-encryption-config.php" title="10.2. Zertifikate richtig erstellen">
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

<a href="base-ssl-encryption.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-ssl-encryption.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">10. Kapitel - SSL-Verschl&uuml;sselung und Zertifikate</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-intranet-local-routing.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;2.&nbsp;Allgemeine Funktionen</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-ssl-encryption-config.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="base-ssl-encryption"></a>10. Kapitel - SSL-Verschl&uuml;sselung und Zertifikate</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="base-ssl-encryption.php#base-ssl-encryption-principle">10.1. Prinzip und Gefahren der SSL-Verschl&uuml;sselung</a></span></dt><dt><span class="sect1"><a href="base-ssl-encryption-config.php">10.2. Zertifikate richtig erstellen</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-ssl-encryption-config.php#base-ssl-encryption-config-servername">10.2.1. Der Rechnername</a></span></dt><dt><span class="sect2"><a href="base-ssl-encryption-config.php#base-ssl-encryption-config-config">10.2.2. Konfiguration</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-ssl-encryption-certinstall.php">10.3. Zertifikate auf Clients installieren</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-ssl-encryption-certinstall.php#base-ssl-encryption-certinstall-windows">10.3.1. Installation unter Windows</a></span></dt><dt><span class="sect2"><a href="base-ssl-encryption-certinstall.php#base-ssl-encryption-certinstall-ad">10.3.2. Verteilen von Zertifikaten &uuml;ber Active Directory</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-ssl-encryption-user.php">10.4. Benutzer sensibilisieren</a></span></dt><dt><span class="sect1"><a href="base-ssl-encryption-ca.php">10.5. Verwenden einer externen Zertifizierungsstelle</a></span></dt><dt><span class="sect1"><a href="base-ssl-encryption-strength.php">10.6. Verschl&uuml;sselungsst&auml;rke</a></span></dt></dl></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-ssl-encryption-principle"></a>10.1. Prinzip und Gefahren der SSL-Verschl&uuml;sselung</h2></div></div></div><a class="indexterm" name="base-ssl-encryption-principle1"></a><a class="indexterm" name="base-ssl-encryption-principle2"></a><p>Durch die Verschl&uuml;sselung wird sichergestellt, dass nur Client und Server die &uuml;bertragenen
      Daten kennen. Was aber passieren kann ist, dass sich jemand beim Verbindungsaufbau zwischen
      Client und Server h&auml;ngt und ab dann alles mitlesen und ver&auml;ndern kann (sog.
        <span class="foreignphrase"><em class="foreignphrase">Man-in-the-middle</em></span>-Angriff). Um das zu verhindern,
      authentifiziert sich der Server beim Verbindungsaufbau mit einem Sicherheitszertifikat
      gegen&uuml;ber dem Client.</p><p>Der Server sendet sein Zertifikat an den Client und dieser &uuml;berpr&uuml;ft es anhand von 3 Kriterien:</p><div class="orderedlist"><ol type="1"><li><p>Aussteller des Zertifikats ist eine dem Client bekannte
            Zertifizierungsstelle.</p></li><li><p>Genau der Server, den der Client kontaktiert hat, ist im Zertifikat als Eigent&uuml;mer
            ausgewiesen. Daf&uuml;r vergleicht der Client den von ihm kontaktierten Rechnernamen mit dem
            Feld Rechnername (<span class="foreignphrase"><em class="foreignphrase">Common Name</em></span>, abgek&uuml;rzt
              <abbr class="abbrev">CN</abbr>) im Zertifikat.</p></li><li><p>Die aktuelle Uhrzeit liegt innerhalb des G&uuml;ltigkeitszeitraums des
            Zertifikats.</p></li></ol></div><p>
    </p><p>Erst, wenn alle 3 Kriterien stimmen, kann sich der Client sicher sein, mit dem richtigen
      Server zu sprechen und ein Angriff kann ausgeschlossen werden.</p><p>Ein in der Praxis tats&auml;chlich beobachteter Angriff sieht wie folgt aus: Ein Hacker sitzt
      mit einem ganz normalen Notebook z.B. an einem WLAN-Hotspot am Flughafen. &Uuml;ber eine spezielle
      Software leitet er alle WLAN-Verbindungen &uuml;ber sein Notebook um. Wenn jemand eine
      verschl&uuml;sselte Verbindung aufbauen m&ouml;chte, pr&auml;sentiert die Software dem Anwender ein anderes
      Zertifikat. Dieses Zertifikat ist ganz legal von einer vertrauensw&uuml;rdigen
      Zertifizierungsstelle auf eine dem Hacker geh&ouml;rende Domain ausgestellt worden. Das einzige was
      bei diesem Angriff den Anwender davor warnen kann, dass die Verbindung vom Hacker abgeh&ouml;rt und
      manipuliert wird, ist der Warnhinweis des Browsers, dass Webseite und Zertifikat nicht
      zusammenpassen.</p><p>Warnungen vor falschen Sicherheitszertifikaten d&uuml;rfen daher nicht ignoriert werden.</p><a class="indexterm" name="d0e1806"></a><a class="indexterm" name="d0e1807"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-intranet-local-routing.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-ssl-encryption-config.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">9.8. Routing im Intranet&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;10.2. Zertifikate richtig erstellen</td></tr></table></div>
      
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