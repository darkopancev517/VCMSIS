<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Offizielle IPs und DMZ | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base-internet.php" title="11. Kapitel - Internet"><link rel="prev" href="base-internet-routerlan.php" title="11.6. Router im lokalen Netz"><link rel="next" href="base-internet-automatic.php" title="11.8. Verbindungsautomatik">
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

<a href="base-internet-official.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-internet-official.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">11.7. Offizielle IPs und DMZ</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-internet-routerlan.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">11. Kapitel - Internet</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-internet-automatic.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-internet-official"></a>11.7. Offizielle IPs und DMZ</h2></div></div></div><a class="indexterm" name="base-internet-official1"></a><a class="indexterm" name="base-internet-official2"></a><a class="indexterm" name="base-internet-official3"></a><p>Stehen mehrere offizielle IPs zur Verf&uuml;gung und soll damit ein Server in einer
      De-Militarized Zone (DMZ) angebunden werden, so kann dies in drei unterschiedlichen Varianten
      erfolgen. </p><div class="note" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Note"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Hinweis]" src="../images/admon/note.png"></td><th align="left">Hinweis</th></tr><tr><td align="left" valign="top"><p>Bitte beachten Sie, dass Sie bei allen Verfahren immer mindestens 8 offizielle IPs
        ben&ouml;tigen, um (mindestens) einen Server in einer DMZ anbinden zu k&ouml;nnen.</p></td></tr></table></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-internet-official-classic"></a>11.7.1. Klassisches Routing</h3></div></div></div><div class="informaltable"><table border="1"><colgroup><col align="left"><col align="left"></colgroup><tbody><tr><td align="left">Vorteile</td><td align="left">einfach verst&auml;ndlich, weit verbreitet</td></tr><tr><td align="left">Nachteile</td><td align="left">Verschwendung von IP-Adressen durch Teilung des Netzes, Subnetz-Routing muss
                auf dem Router eingetragen werden</td></tr></tbody></table></div><p>Bei dieser Variante wird das vorhandene Netz mit offiziellen IPs in zwei kleinere
        Subnetze geteilt: Ein sog. Transfernetz zwischen Router und Intranator und ein DMZ-Netz. Da
        pro Subnetz immer zwei IPs f&uuml;r Netzadresse und Broadcast ben&ouml;tigt werden und der Intranator
        in beiden Netzen eine IP ben&ouml;tigt, steht von 8 offiziellen IPs am Ende nur eine f&uuml;r einen
        Server in der DMZ zur Verf&uuml;gung.</p><p>Auf dem Router muss eingestellt werden, dass das direkt angeschlossene Netz
        (Transfernetz) verkleinert wurde und dass das DMZ-Netz &uuml;ber den Intranator geroutet wird. Da
        der Benutzer auf einen vom Provider gestellten Router oft keinen Zugriff hat, muss diese
        Einstellung der Provider f&uuml;r Sie vornehmen.</p><p>
        </p><div class="mediaobject"><img src="../images/base/public-classic.png"></div><p>
      </p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-internet-official-snat"></a>11.7.2. Statische NAT</h3></div></div></div><a class="indexterm" name="base-internet-official-snat1"></a><div class="informaltable"><table border="1"><colgroup><col align="left"><col align="left"></colgroup><tbody><tr><td align="left">Vorteile</td><td align="left">flexibel, gute Ausnutzung der IPs</td></tr><tr><td align="left">Nachteile</td><td align="left">funktioniert nicht mit allen Protokollen</td></tr></tbody></table></div><p>Bei dieser Variante wird die DMZ wie ein normales LAN mit IPs aus dem privaten
        Adressraum (z.B. 192.168.x.x) eingerichtet. Legen Sie alle DMZ-Server unter Netzwerk
        &gt; Intranet &gt; Rechner an. Im Men&uuml; Netzwerk &gt; Firewall &gt; Statische
        NAT wird dann eine Weiterleitung der offiziellen IP auf den Server in der DMZ
        konfiguriert.</p><p>Der Intranator legt automatisch ein virtuelles Netzwerkinterface beim Provider an,
        sobald die offizielle IP im Netz zwischen Router und Intranator liegt. Deshalb ben&ouml;tigen Sie
        auf dem Router keine speziellen Routingeintr&auml;ge f&uuml;r diese IPs.</p><p>Da der Server nur seine IP aus dem LAN - nicht aber seine offizielle - kennt,
        funktionieren manche Protokolle nicht, denn einige Protokolle &uuml;bertragen zus&auml;tzlich die
        verwendete IP im normalen Datenstrom. Bei einigen Protokollen kann der Intranator dies
        kompensieren (z.B. FTP und PPTP), bei anderen aber nicht (z.B. H.323).</p><p>
        </p><div class="mediaobject"><img src="../images/base/public-snat.png"></div><p>
      </p><a class="indexterm" name="d0e2437"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-internet-official-proxyarp"></a>11.7.3. Proxy-ARP</h3></div></div></div><a class="indexterm" name="base-internet-official-proxyarp1"></a><a class="indexterm" name="base-internet-official-proxyarp2"></a><div class="informaltable"><table border="1"><colgroup><col align="left"><col align="left"></colgroup><tbody><tr><td align="left">Vorteile</td><td align="left">funktioniert mit allen Protokollen, gute Ausnutzung der IPs</td></tr><tr><td align="left">Nachteile</td><td align="left">komplexere Konfiguration</td></tr></tbody></table></div><p>Bei Proxy-ARP wird das Netz zwischen Router und Intranator mit den gleichen Daten ein
        weiteres mal als DMZ angelegt. Unter Netzwerk &gt; Interfaces tragen Sie f&uuml;r die DMZ den
        Typ "Proxy-ARP" ein. Geben Sie dem Intranator in diesem Netz die gleiche IP wie Sie sie auch
        unter Netzwerk &gt; Provider &gt; Profile eingetragen haben. Tragen Sie unbedingt
        alle Rechner in dem DMZ-Netz einzeln unter Netzwerk &gt; Intranet &gt; Rechner ein.
        Der Intranator geht davon aus, dass alle dort nicht eingetragenen Rechner in dem Netz
        zwischen Intranator und Router liegen.</p><p>Stellen Sie das Default-Gateway auf dem Server in der DMZ auf den Intranator. Der
        Intranator vermittelt jetzt zwischen den beiden Netzteilen, ohne dass die beteiligten
        Rechner davon etwas mitbekommen. F&uuml;r die Rechner sieht es so aus, als ob es sich um ein
        einzelnes, gr&ouml;&szlig;eres Netz handelt. Selbstverst&auml;ndlich kontrolliert die Firewall den
        Datenverkehr zwischen den beiden Netzteilen.</p><p>Auf dem Router m&uuml;ssen Sie f&uuml;r das interne Netz keine speziellen Einstellungen
        vornehmen.</p><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Bei der Erstinstallation kann es leicht zu Problemen mit dem ARP-Cache des Routers
          kommen. Der Router denkt dann, dass der Server noch im Netz zwischen Router und Intranator
          liegt. Konfigurieren Sie zuerst den Intranator, dann den Server in der DMZ und starten
          danach den Router neu um dieses Problem zu vermeiden.</p></td></tr></table></div><p>
        </p><div class="mediaobject"><img src="../images/base/public-proxyarp.png"></div><p>
      </p><a class="indexterm" name="d0e2479"></a><a class="indexterm" name="d0e2480"></a><a class="indexterm" name="d0e2481"></a><a class="indexterm" name="d0e2482"></a><a class="indexterm" name="d0e2483"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-internet-routerlan.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base-internet.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-internet-automatic.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">11.6. Router im lokalen Netz&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;11.8. Verbindungsautomatik</td></tr></table></div>
      
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