<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Domain und DNS | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base-intranet.php" title="9. Kapitel - Intranet"><link rel="prev" href="base-intranet-rights.php" title="9.2. Zugriffsrechte eines Netzwerkobjekts"><link rel="next" href="base-intranet-clients.php" title="9.4. Clients eintragen">
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

<a href="base-intranet-dns.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-intranet-dns.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">9.3. Domain und DNS</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-intranet-rights.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">9. Kapitel - Intranet</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-intranet-clients.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-intranet-dns"></a>9.3. Domain und DNS</h2></div></div></div><a class="indexterm" name="base-intranet-dns1"></a><a class="indexterm" name="base-intranet-dns2"></a><p>Der Intranator leitet DNS-Anfragen ins Internet weiter. Wie und wohin wird beim aktuell
      aktiven Provider eingestellt, siehe <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-internet.php">11. Kapitel,&nbsp;&#8222;Internet&#8220;</a>.</p><p>Au&szlig;erdem kann er entweder selbst f&uuml;r die lokale Domain als DNS-Server fungieren oder diese
      Aufgabe an einen anderen Server delegieren.</p><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-intranet-dns-local-self"></a>9.3.1. DNS-Server f&uuml;r Lokale Domain</h3></div></div></div><p>Der eigene Rechnername und die lokale Domain k&ouml;nnen unter
        Netzwerk&nbsp;&gt;&nbsp;DNS&nbsp;&gt;&nbsp;Einstellungen eingestellt
        werden. Stellen Sie ein, dass das lokale System f&uuml;r die lokale Domain zust&auml;ndig ist.</p><p>Der Intranator ist dann DNS-Server f&uuml;r die lokale Domain. Alle unter
        Netzwerk&nbsp;&gt;&nbsp;Intranet&nbsp;&gt;&nbsp;Rechner
        eingetragenen Rechnernamen k&ouml;nnen per DNS aufgel&ouml;st werden.</p><p>Es wird dringend davon abgeraten, die offizielle Domain einer Firma (z.B.
        &#8222;meinefirma.de&#8220;) auch im lokalen Netz zu verwenden. Da der Intranator ja DNS-Server f&uuml;r die
        lokale Domain ist, kann er Anfragen f&uuml;r die im externen DNS-Server des Web-Providers
        konfigurierten Rechner, wie z.B. &#8222;www&#8220;, nicht beantworten.</p><p>Verwenden Sie stattdessen eine nur lokal g&uuml;ltige Domain, wie z.B. &#8222;meinefirma.lan&#8220;.
        Wegen einem Internet-Standard zu Broadcast-DNS empfehlen wir auch, f&uuml;r diese Domains nicht
        &#8222;.local&#8220; zu verwenden, denn mit einigen Mac OS oder Linux-Versionen funktioniert die
        Namensaufl&ouml;sung nicht mehr, wenn &#8222;.local&#8220; in der lokalen Domain verwendet wird.</p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-intranet-dns-local-redirect"></a>9.3.2. DNS f&uuml;r lokale Domain weiterleiten</h3></div></div></div><a class="indexterm" name="base-intranet-dns3"></a><p>Verwenden Sie einen anderen DNS-Server f&uuml;r die lokale Domain (z.B. einen Windows Domain
        Controller), tragen Sie den Rechnernamen und die Domain des Intranators unter
        Netzwerk&nbsp;&gt;&nbsp;DNS&nbsp;&gt;&nbsp;Einstellungen ein.
        Stellen Sie die Zust&auml;ndigkeit f&uuml;r die lokale Domain auf <span class="guimenuitem">anderer
          Server</span>. Tragen Sie die IP des zust&auml;ndigen DNS-Servers und (wenn vorhanden)
        des alternativen Servers in die Felder <span class="guimenuitem">1.</span> und
          <span class="guimenuitem">2.</span> ein.</p><p>Hinterlegen Sie unbedingt auf diesen DNS-Servern einen A-Eintrag f&uuml;r den Intranator mit
        seiner IP.</p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-intranet-dns-redirect"></a>9.3.3. DNS f&uuml;r andere Domains weiterleiten</h3></div></div></div><p>Der Intranator kann Anfragen f&uuml;r andere nicht-&ouml;ffentliche Domains an fest hinterlegte
        Server weiterleiten. Dies macht z.B. Sinn, wenn verschiedene Standorte per VPN verbunden sind
        und Namen in den lokalen Domains der jeweils anderen Standorte aufgel&ouml;st werden k&ouml;nnen
        sollen.</p><p>Tragen Sie diese Domains und die IPs der zugeh&ouml;rigen DNS-Server unter
        Netzwerk&nbsp;&gt;&nbsp;DNS&nbsp;&gt;&nbsp;Weiterleitung ein.</p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-intranet-dns-rebind"></a>9.3.4. DNS-Rebind verhindern</h3></div></div></div><a class="indexterm" name="base-intranet-dns-rebind1"></a><p>Bei einem sogenannten DNS-Rebind-Angriff liefert ein externer DNS-Server eine IP aus dem
        lokalen Netz zur&uuml;ck. Dadurch kann ein externer Angreifer einen Webbrowser dazu bringen,
        ferngesteuert Verbindungen ins Lokale Netz aufzubauen. Details zu diesem Angriff finden Sie
          <a class="ulink" href="http://en.wikipedia.org/wiki/DNS_rebinding" target="_top">bei Wikipedia</a>.</p><p>Der Intranator kann diese Angriffe wirkungsvoll verhindern, indem er Antworten mit
        lokalen IPs von externen DNS-Servern blockiert. Damit das nicht zu St&ouml;rungen f&uuml;hrt, d&uuml;rfen
        unter
        Netzwerk&nbsp;&gt;&nbsp;Provider&nbsp;&gt;&nbsp;Profile&nbsp;:&nbsp;Einstellungen
        nur tats&auml;chlich extern liegende DNS-Server eingetragen sein.</p><p>Alle DNS-Server, die f&uuml;r lokale oder lokal geroutete Domains zust&auml;ndig sind, m&uuml;ssen unter
        den entsprechenden Domains als DNS-Weiterleitung konfiguriert werden. Die dort hinterlegten
        Server d&uuml;rfen dann mit lokalen IPs antworten.</p><a class="indexterm" name="d0e1597"></a><a class="indexterm" name="d0e1598"></a><a class="indexterm" name="d0e1599"></a><a class="indexterm" name="d0e1600"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-intranet-rights.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base-intranet.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-intranet-clients.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">9.2. Zugriffsrechte eines Netzwerkobjekts&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;9.4. Clients eintragen</td></tr></table></div>
      
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