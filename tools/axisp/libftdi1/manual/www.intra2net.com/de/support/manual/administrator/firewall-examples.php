<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Fallbeispiele und Aufgaben | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="firewall.php" title="Teil&nbsp;5.&nbsp;Firewall"><link rel="prev" href="firewall-additional-functions-emergency.php" title="36.4. Firewall-Notmodus"><link rel="next" href="firewall-examples-external-https.php" title="37.2. Aufgabe 2: Oberfl&auml;che nur f&uuml;r eine externe IP erreichbar">
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

<a href="firewall-examples.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="firewall-examples.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">37. Kapitel - Fallbeispiele und Aufgaben</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="firewall-additional-functions-emergency.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;5.&nbsp;Firewall</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="firewall-examples-external-https.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="firewall-examples"></a>37. Kapitel - Fallbeispiele und Aufgaben</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="firewall-examples.php#firewall-examples-add-access">37.1. Aufgabe 1: Erweitern eines einfachen Rechnerprofils</a></span></dt><dd><dl><dt><span class="sect2"><a href="firewall-examples.php#d0e11622">37.1.1. Musterl&ouml;sung</a></span></dt></dl></dd><dt><span class="sect1"><a href="firewall-examples-external-https.php">37.2. Aufgabe 2: Oberfl&auml;che nur f&uuml;r eine externe IP erreichbar</a></span></dt><dd><dl><dt><span class="sect2"><a href="firewall-examples-external-https.php#d0e11650">37.2.1. Musterl&ouml;sung</a></span></dt></dl></dd><dt><span class="sect1"><a href="firewall-examples-guestlan.php">37.3. Aufgabe 3: Separiertes G&auml;stenetz</a></span></dt><dd><dl><dt><span class="sect2"><a href="firewall-examples-guestlan.php#d0e11681">37.3.1. Musterl&ouml;sung</a></span></dt></dl></dd><dt><span class="sect1"><a href="firewall-examples-vpn.php">37.4. Aufgabe 4: Beschr&auml;nkter Zugang aus dem VPN</a></span></dt><dd><dl><dt><span class="sect2"><a href="firewall-examples-vpn.php#d0e11725">37.4.1. Musterl&ouml;sung</a></span></dt></dl></dd><dt><span class="sect1"><a href="firewall-examples-dmz.php">37.5. Aufgabe 5: Webserver in der DMZ</a></span></dt><dd><dl><dt><span class="sect2"><a href="firewall-examples-dmz.php#d0e11782">37.5.1. Musterl&ouml;sung</a></span></dt></dl></dd></dl></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="firewall-examples-add-access"></a>37.1. Aufgabe 1: Erweitern eines einfachen Rechnerprofils</h2></div></div></div><p>Gegeben ist folgendes einfaches Rechnerprofil:</p><div class="itemizedlist"><ul type="disc"><li><p>Zugriffsberechtigung: WWW/FTP/E-Mail/News</p></li><li><p>Zugriff auf lokale Netze nicht erlaubt</p></li><li><p>keine zus&auml;tzlichen Dienste freigegeben</p></li><li><p>Webzugriff &uuml;ber Proxy: Proxyzwang</p></li><li><p>Faxversand erlaubt: aktiv</p></li><li><p>E-Mail-Transfer nur &uuml;ber Intranator: aktiv</p></li></ul></div><p>Legen Sie dieses Rechnerprofil an. Wandeln Sie es dann in eine vollst&auml;ndige
      Firewallregelliste um und f&uuml;gen eine Regel hinzu, die den Zugriff per RDP-Protokoll auf einen
      Server im Internet mit der IP 11.22.33.44 erlaubt.</p><p>Legen Sie einen Rechner mit dem Namen "R10" und der IP 192.168.1.10 an und weisen ihm
      diese Firewallregelliste zu.</p><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="d0e11622"></a>37.1.1. Musterl&ouml;sung</h3></div></div></div><p>Anlegen einer Netzgruppe f&uuml;r den Rechner 11.22.33.44 unter Netzwerk &gt; Firewall
        &gt; Netzgruppen</p><div class="screenshot"><div class="mediaobject"><img src="../images/firewall/examples/aufg1a.png"></div></div><p>Firewall Regelliste</p><div class="screenshot"><div class="mediaobject"><img src="../images/firewall/examples/aufg1b.png"></div></div><p>Dem Rechner R10 die neue Firewall Regelliste zuweisen</p><div class="screenshot"><div class="mediaobject"><img src="../images/firewall/examples/aufg1c.png"></div></div></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="firewall-additional-functions-emergency.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="firewall.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="firewall-examples-external-https.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">36.4. Firewall-Notmodus&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;37.2. Aufgabe 2: Oberfl&auml;che nur f&uuml;r eine externe IP erreichbar</td></tr></table></div>
      
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