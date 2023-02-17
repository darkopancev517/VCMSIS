<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Einstellungen auf dem Server | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="webgroupware-activesync.php" title="29. Kapitel - Mobile Ger&auml;te per ActiveSync anbinden"><link rel="prev" href="webgroupware-activesync.php" title="29. Kapitel - Mobile Ger&auml;te per ActiveSync anbinden"><link rel="next" href="webgroupware-activesync-tips.php" title="29.3. Besonderheiten und Tipps">
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

<a href="webgroupware-activesync-serverconfig.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="webgroupware-activesync-serverconfig.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">29.2. Einstellungen auf dem Server</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="webgroupware-activesync.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">29. Kapitel - Mobile Ger&auml;te per ActiveSync anbinden</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="webgroupware-activesync-tips.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="webgroupware-activesync-serverconfig"></a>29.2. Einstellungen auf dem Server</h2></div></div></div><p>Um Ger&auml;te per ActiveSync mit dem Intranator Server zu verbinden, m&uuml;ssen auf dem Server
            zuerst folgende Grundeinstellungen vorgenommen bzw. &uuml;berpr&uuml;ft werden:</p><div class="procedure"><ol type="1"><li><p>Pr&uuml;fen Sie, wie der Intranator mit dem Internet verbunden ist. Kontrollieren
                    Sie dazu im Men&uuml;
                        <span class="guimenu">Netzwerk&nbsp;&gt;&nbsp;Provider&nbsp;&gt;&nbsp;Profile</span>
                    den Typ des aktiven Providers. Handelt es sich um eine (DSL-)Wahlleitung ist
                    alles in Ordnung und Sie k&ouml;nnen zum n&auml;chsten Schritt weitergehen.</p><p>Handelt es sich um einen Providertyp mit einem Router, dann pr&uuml;fen Sie ob
                    dieser Router dem Intranator Server eine unver&auml;nderte offizielle IP zuweist,
                    oder ob er per NAT eine IP aus einem privaten Adressbereich zuweist. In
                    letzterem Fall muss auf dem Router ein Portforwarding f&uuml;r TCP Port 443 (https)
                    auf die IP des Intranator Servers konfiguriert werden.</p></li><li><p>Kontrollieren Sie die Firewall-Regelliste f&uuml;r aus dem Internet eingehende
                    Verbindungen. Sie wird im Men&uuml;
                        <span class="guimenu">Netzwerk&nbsp;&gt;&nbsp;Provider&nbsp;&gt;&nbsp;Profile&nbsp;:&nbsp;Firewall</span>
                    f&uuml;r den aktiven Provider ausgew&auml;hlt und kann mit dem Lupen-Symbol untersucht
                    werden. In ihr m&uuml;ssen <span class="guimenuitem">Eingehende HTTPS-Verbindungen</span>
                    aktiviert sein.</p></li><li><p>Der Intranator muss f&uuml;r das Mobilger&auml;t &uuml;ber das Internet adressierbar
                    sein.</p><p>Bekommt der Intranator bei der Interneteinwahl regelm&auml;&szlig;ig eine neue IP
                    zugewiesen, muss zur Adressierung ein DynDNS-Dienst eingerichtet werden. Siehe
                    hierf&uuml;r <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-internet-dyndns.php">Abschnitt&nbsp;11.12, &#8222;DynDNS&#8220;</a>.</p><p>Hat der Intranator eine feste IP, empfehlen wir dringend f&uuml;r diese feste IP
                    einen DNS-Eintrag in der eigenen offiziellen Domain einzurichten. Der Intranator
                    ist dann unter einem Namen wie z.B.
                        <strong class="userinput"><code>intranator.kundenname.de</code></strong> oder
                        <strong class="userinput"><code>mail.example.com</code></strong> erreichbar. Dies kann normalerweise
                    beim Webspace-Provider, der die eigene Domain verwaltet, kostenlos und zeitnah
                    eingerichtet werden.</p><p>Eine feste IP direkt und ohne DNS-Namen sollte nur in Ausnahmef&auml;llen f&uuml;r
                    ActiveSync verwendet werden. Hintergrund ist, dass bei einer &Auml;nderung der IP
                    alle Ger&auml;te neu eingerichtet werden m&uuml;ssen und offizielle Zertifizierungsstellen
                    keine Zertifikate f&uuml;r IPs ausstellen.</p></li><li><p>Der Zugriff auf ActiveSync findet ausschlie&szlig;lich &uuml;ber HTTPS statt. F&uuml;r die
                    Verschl&uuml;sselung wird daher ein passendes Zertifikat ben&ouml;tigt, welches auf den
                    verwendeten externen DNS-Namen (siehe oben) ausgestellt ist. Dieses Zertifikat
                    muss im Men&uuml;
                        <span class="guimenu">System&nbsp;&gt;&nbsp;Weboberfl&auml;che&nbsp;&gt;&nbsp;Sicherheit</span>
                    als <span class="guimenuitem">SSL Server Schl&uuml;ssel f&uuml;r Verbindungen aus dem
                        Internet</span> gew&auml;hlt sein.</p><p>Mehr Informationen zu SSL und Zertifikaten finden Sie im <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-ssl-encryption.php">10. Kapitel,&nbsp;&#8222;SSL-Verschl&uuml;sselung und Zertifikate&#8220;</a>.</p><div class="tip" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Tip"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Tipp]" src="../images/admon/tip.png"></td><th align="left">Tipp</th></tr><tr><td align="left" valign="top"><p>Wir empfehlen ab ca. 5 anzubindenden Ger&auml;ten oder Benutzern ein Zertifikat
                        von einer offiziellen Zertifizierungsstelle zu verwenden. Dies vereinfacht
                        die Administration, da die Ger&auml;te dann zur Ersteinrichtung nicht unbedingt
                        &uuml;ber eine vertrauensw&uuml;rdige Netzumgebung verbunden werden m&uuml;ssen.</p><p>Wie Sie das Zertifikat einer offiziellen Zertifizierungsstelle mit dem
                        Intranator verwenden wird in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-ssl-encryption-ca.php">Abschnitt&nbsp;10.5, &#8222;Verwenden einer externen Zertifizierungsstelle&#8220;</a> erkl&auml;rt.</p></td></tr></table></div></li><li><p>Pr&uuml;fen Sie die Qualit&auml;t der Passw&ouml;rter aller Benutzer, die ActiveSync
                    verwenden sollen. Die Passw&ouml;rter sollten ausreichend lang (mindestens 8
                    Stellen), aus Buchstaben, Zahlen und evtl. auch Sonderzeichen zusammengesetzt
                    sein und nicht zu einem gro&szlig;en Teil aus einem Wort oder Eigennamen einer
                    verbreiteten Sprache bestehen.</p></li><li><p>Bevor ein Benutzer ActiveSync verwenden darf, muss in einer seiner
                    Benutzergruppen das Recht <span class="guimenuitem">Zugriff auf Groupware-Daten via
                        ActiveSync</span> (Men&uuml;
                        <span class="guimenu">Benutzermanager&nbsp;&gt;&nbsp;Gruppen&nbsp;:&nbsp;Rechte</span>)
                    vergeben sein.</p><div class="tip" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Tip"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Tipp]" src="../images/admon/tip.png"></td><th align="left">Tipp</th></tr><tr><td align="left" valign="top"><p>Wir empfehlen f&uuml;r ActiveSync eine separate Benutzergruppe einzurichten,
                        und in diese wirklich nur Benutzer mit &uuml;berpr&uuml;fter Passwortqualit&auml;t (siehe
                        oben) aufzunehmen.</p></td></tr></table></div></li><li><p>ActiveSync &uuml;bertr&auml;gt f&uuml;r jeden Objekttyp immer nur die Daten aus einem
                    einzigen Ordner. Stellen Sie daher f&uuml;r jeden Benutzer im Men&uuml;
                        <span class="guimenu">Benutzermanager&nbsp;&gt;&nbsp;Benutzer&nbsp;:&nbsp;Groupware</span>
                    die Ordner als Standardordner ein, die auch per ActiveSync &uuml;bertragen werden
                    sollen.</p></li><li><p>Konfigurieren Sie die einzelnen Ger&auml;te wie in den folgenden Kapiteln
                    beschrieben.</p></li></ol></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="webgroupware-activesync.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="webgroupware-activesync.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="webgroupware-activesync-tips.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">29. Kapitel - Mobile Ger&auml;te per ActiveSync anbinden&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;29.3. Besonderheiten und Tipps</td></tr></table></div>
      
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