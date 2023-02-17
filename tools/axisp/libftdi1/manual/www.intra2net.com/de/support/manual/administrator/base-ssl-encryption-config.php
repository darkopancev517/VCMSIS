<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Zertifikate richtig erstellen | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base-ssl-encryption.php" title="10. Kapitel - SSL-Verschl&uuml;sselung und Zertifikate"><link rel="prev" href="base-ssl-encryption.php" title="10. Kapitel - SSL-Verschl&uuml;sselung und Zertifikate"><link rel="next" href="base-ssl-encryption-certinstall.php" title="10.3. Zertifikate auf Clients installieren">
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

<a href="base-ssl-encryption-config.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-ssl-encryption-config.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">10.2. Zertifikate richtig erstellen</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-ssl-encryption.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">10. Kapitel - SSL-Verschl&uuml;sselung und Zertifikate</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-ssl-encryption-certinstall.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-ssl-encryption-config"></a>10.2. Zertifikate richtig erstellen</h2></div></div></div><a class="indexterm" name="base-ssl-encryption-config1"></a><a class="indexterm" name="base-ssl-encryption-config2"></a><a class="indexterm" name="base-ssl-encryption-config3"></a><a class="indexterm" name="base-ssl-encryption-config4"></a><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-ssl-encryption-config-servername"></a>10.2.1. Der Rechnername</h3></div></div></div><p>Der Name, (oder die IP) den Sie im Webbrowser, E-Mail-Programm etc. eingeben um den
        Server anzusprechen, muss genau mit dem Feld Rechnername (CN) im Zertifikat &uuml;bereinstimmen.
        Das hei&szlig;t, wenn Sie den Intranator z.B. &uuml;ber die Rechnernamen
          <strong class="userinput"><code>intranator.net.lan</code></strong> und
          <strong class="userinput"><code>meinintranator.dyndns.org</code></strong> ansprechen wollen, ben&ouml;tigen Sie 2
        verschiedene Zertifikate.</p><p>Der Intranator bietet daher die M&ouml;glichkeit, ein Zertifikat f&uuml;r die interne
        Schnittstelle und ein anderes f&uuml;r die Internet-Schnittstelle zu konfigurieren.</p><p>Damit die Pr&uuml;fung des Rechnernamens durchg&auml;ngig funktionieren kann, muss der Intranator
        von allen Clients im lokalen Netz unter seinem konfigurierten DNS-Namen erreichbar sein.
        Beachten Sie daher unbedingt <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-intranet-dns.php">Abschnitt&nbsp;9.3, &#8222;Domain und DNS&#8220;</a>
        und testen, ob der Intranator unter seinem vollst&auml;ndigen Namen (also inkl. Domain) auch von
        den Clients im lokalen Netz erreichbar ist.</p><p>Wir raten davon ab, eine IP-Adresse als Rechnernamen im Zertifikat zu
        hinterlegen.</p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-ssl-encryption-config-config"></a>10.2.2. Konfiguration</h3></div></div></div><p>&Ouml;ffnen Sie die Seite
        System&nbsp;&gt;&nbsp;Schl&uuml;ssel&nbsp;&gt;&nbsp;Eigene Schl&uuml;ssel und
        legen einen neuen Schl&uuml;ssel an. Der Name ist egal, es macht aber Sinn, hier den Rechnernamen
        zu verwenden.</p><p>Als Schl&uuml;ssell&auml;nge empfehlen Institutionen wie das BSI bzw. Bundesnetzagentur momentan
        2048 Bit (siehe Algorithmenkatalog bei der Bundesnetzagentur).</p><p>Tragen Sie in das Feld <span class="guimenuitem">Rechnername (CN)</span> den Rechnernamen
        (siehe oben) ein. Alle anderen Felder k&ouml;nnen Sie entweder leer lassen oder nach Belieben
        f&uuml;llen.</p><p>Wurde der Schl&uuml;ssel angelegt, k&ouml;nnen Sie ihn unter
        System&nbsp;&gt;&nbsp;Weboberfl&auml;che&nbsp;&gt;&nbsp;Sicherheit
        verwenden. Bei <span class="guimenuitem">Server Schl&uuml;ssel f&uuml;r SSL</span> w&auml;hlen Sie den Schl&uuml;ssel
        aus, der f&uuml;r Verbindungen aus dem lokalen Netz genutzt werden soll. Bei <span class="guimenuitem">SSL
          Server Schl&uuml;ssel f&uuml;r Verbindungen aus dem Internet</span> w&auml;hlen Sie den Schl&uuml;ssel
        f&uuml;r Verbindungen aus dem Internet.</p><a class="indexterm" name="d0e1870"></a><a class="indexterm" name="d0e1871"></a><a class="indexterm" name="d0e1872"></a><a class="indexterm" name="d0e1873"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-ssl-encryption.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base-ssl-encryption.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-ssl-encryption-certinstall.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">10. Kapitel - SSL-Verschl&uuml;sselung und Zertifikate&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;10.3. Zertifikate auf Clients installieren</td></tr></table></div>
      
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