<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Auswahl der Firewall-Regellisten | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="firewall.php" title="Teil&nbsp;5.&nbsp;Firewall"><link rel="prev" href="firewall.php" title="Teil&nbsp;5.&nbsp;Firewall"><link rel="next" href="firewall-rule-selection-internet.php" title="33.2. Regellisten f&uuml;rs Internet">
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

<a href="firewall-rule-selection.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="firewall-rule-selection.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">33. Kapitel - Auswahl der Firewall-Regellisten</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="firewall.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;5.&nbsp;Firewall</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="firewall-rule-selection-internet.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="firewall-rule-selection"></a>33. Kapitel - Auswahl der Firewall-Regellisten</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="firewall-rule-selection.php#firewall-rule-selection-lan">33.1. Regellisten im LAN</a></span></dt><dt><span class="sect1"><a href="firewall-rule-selection-internet.php">33.2. Regellisten f&uuml;rs Internet</a></span></dt><dt><span class="sect1"><a href="firewall-rule-selection-packetway.php">33.3. Weg der Pakete durch die Firewall</a></span></dt><dd><dl><dt><span class="sect2"><a href="firewall-rule-selection-packetway.php#d0e10977">33.3.1. Paketwege im LAN und Internet</a></span></dt><dt><span class="sect2"><a href="firewall-rule-selection-packetway.php#d0e11001">33.3.2. Paketwege bei VPN-Verbindungen</a></span></dt></dl></dd></dl></div><a class="indexterm" name="firewall-rule-selection1"></a><p>Die Firewall des Intranators besteht aus einzelnen, separaten Firewall-Regellisten. Diese
    Regellisten k&ouml;nnen einzelnen Objekten, wie z.B. Rechnern oder Netzen, zugewiesen werden. Beim
    Anlegen eines neuen Objekts kann eine bestehende Firewallregelliste wiederverwendet werden.
    Au&szlig;erdem werden die wichtigsten Grundregeln schon vorinstalliert mitgeliefert. Dies vereinfacht
    die Konfiguration deutlich.</p><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="firewall-rule-selection-lan"></a>33.1. Regellisten im LAN</h2></div></div></div><a class="indexterm" name="firewall-rule-selection-lan1"></a><p>Jedem Rechner, IP-Bereich, Routing, Netz und VPN kann &uuml;ber das passende Men&uuml; (z.B.
      &#8222;Netzwerk &gt; Intranet &gt; Rechner&#8220; genau eine Firewall-Regelliste zugewiesen
      werden.</p><p>Da sich Rechner oder IP-Bereiche gleichzeitig auch immer in einem Netz oder Routing
      befinden, sind ihnen 2 Firewall-Regellisten zugeordnet. Hier gilt immer nur die dem Rechner
      oder IP-Bereich zugeordnete Regel, die dem Netz oder Routing zugeordnete kommt nicht zum
      Einsatz. Diese gelten nur f&uuml;r IPs aus dem Netz, f&uuml;r die kein Rechner oder IP-Bereich
      konfiguriert ist.</p><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Allein die Quelle eines Pakets entscheidet, welche Firewall-Regelliste verwendet
        wird.</p></td></tr></table></div><p>Daher finden Sie in einer Regelliste f&uuml;r einen Rechner sowohl Regeln f&uuml;r den Zugriff auf
      andere lokale Netze als auch ins Internet, in VPNs etc. Alles was von einem Rechner kommt wird
      unabh&auml;ngig vom Ziel anhand der dem Rechner zugewiesenen Regelliste &uuml;berpr&uuml;ft.</p><p>In dem Rechteblock f&uuml;r z.B. einen Rechner finden Sie au&szlig;er der Firewall-Regelliste auch
      noch Einstellungen zum Proxy-Profil sowie zum DNS- und E-Mail-Relaying. Die
      Firewall-Regelliste hat Vorrang vor diesen Einstellungen. Das hei&szlig;t, erst, wenn die
      Firewall-Regelliste den Zugriff auf den Proxy zul&auml;sst, kommt die Einstellung des Proxy-Profils
      &uuml;berhaupt zum Tragen.</p><a class="indexterm" name="d0e10958"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="firewall.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="firewall.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="firewall-rule-selection-internet.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">Teil&nbsp;5.&nbsp;Firewall&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;33.2. Regellisten f&uuml;rs Internet</td></tr></table></div>
      
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